#!/usr/bin/env python2.7

import sys, os
import struct
import hashlib
import re

NID_SUFFIX = '518D64A635DED8C1E6B039B1C3E55230'.decode('hex')

def check_file_magic(f, expected_magic):
	old_offset = f.tell()
	try:
		magic = f.read(len(expected_magic))
	except:
		return False
	finally:
		f.seek(old_offset)
	return magic == expected_magic

def sha1(data):
	return hashlib.sha1(data).digest()

def calculate_nid(symbol):
	return struct.unpack('<Q', sha1(symbol + NID_SUFFIX)[:8])[0]

class ElfProgramHeader64(object):
	FMT = '<2I6Q'

	PT_NULL = 0x0
	PT_LOAD = 0x1
	PT_SCE_DYNLIBDATA = 0x61000000
	PT_SCE_RELRO = 0x61000010
	PT_SCE_COMMENT = 0x6FFFFF00
	PT_SCE_VERSION = 0x6FFFFF01

	PF_X = 0x1
	PF_W = 0x2
	PF_R = 0x4
	PF_RX = PF_R | PF_X
	PF_RW = PF_R | PF_W

	def __init__(self):
		self.type = None
		self.flags = None
		self.offset = None
		self.vaddr = None
		self.paddr = None
		self.file_size = None
		self.mem_size = None
		self.align = None

	def load(self, f):
		data = f.read(struct.calcsize(ElfProgramHeader64.FMT))
		if len(data) != struct.calcsize(ElfProgramHeader64.FMT):
			return False
		self.type, self.flags, self.offset, self.vaddr, self.paddr, self.file_size, self.mem_size, self.align = struct.unpack(ElfProgramHeader64.FMT, data)
		return True

class ElfSectionHeader64(object):
	FMT = '<2I4Q2I2Q'

	SHT_STRTAB = 0x3
	SHT_DYNSYM = 0xB
	SHT_SCENID = 0x61000001

	def __init__(self):
		self.name = None
		self.type = None
		self.flags = None
		self.addr = None
		self.offset = None
		self.size = None
		self.link = None
		self.info = None
		self.align = None
		self.entry_size = None

	def load(self, f):
		data = f.read(struct.calcsize(ElfSectionHeader64.FMT))
		if len(data) != struct.calcsize(ElfSectionHeader64.FMT):
			return False
		self.name, self.type, self.flags, self.addr, self.offset, self.size, self.link, self.info, self.align, self.entry_size = struct.unpack(ElfSectionHeader64.FMT, data)
		return True

class ElfSym64(object):
	FMT = '<I2BHQQ'

	def __init__(self):
		self.name = None
		self.info = None
		self.other = None
		self.shndx = None
		self.value = None
		self.size = None

	def load(self, f):
		data = f.read(struct.calcsize(ElfSym64.FMT))
		if len(data) != struct.calcsize(ElfSym64.FMT):
			return False
		self.name, self.info, self.other, self.shndx, self.value, self.size = struct.unpack(ElfSym64.FMT, data)
		return True

class ElfNid(object):
	FMT = '<Q'

	def __init__(self):
		self.value = None

	def load(self, f):
		data = f.read(struct.calcsize(ElfNid.FMT))
		if len(data) != struct.calcsize(ElfNid.FMT):
			return False
		self.value, = struct.unpack(ElfNid.FMT, data)
		return True

	def save(self, f):
		data = struct.pack(ElfNid.FMT, self.value)
		if len(data) != struct.calcsize(ElfNid.FMT):
			return False
		f.write(data)
		return True

class ElfFile64(object):
	MAGIC = '\x7FELF'

	FMT = '<4s5B6xB2HI3QI6H'

	CLASS_NONE = 0
	CLASS_64 = 2

	DATA_NONE = 0
	DATA_LSB = 1

	VERSION_CURRENT = 1

	TYPE_EXEC = 0x2
	TYPE_DYN = 0x3
	TYPE_SCE_EXEC = 0xFE00
	TYPE_SCE_STUB = 0xFE0C
	TYPE_SCE_EXEC_ASLR = 0xFE10
	TYPE_SCE_DYNAMIC = 0xFE18

	MACHINE_X86_64 = 0x3E

	def __init__(self):
		self.magic = None
		self.cls = None
		self.encoding = None
		self.legacy_version = None
		self.os_abi = None
		self.abi_version = None
		self.nident_size = None
		self.type = None
		self.machine = None
		self.version = None
		self.entry = None
		self.phdr_offset = None
		self.shdr_offset = None
		self.flags = None
		self.ehdr_size = None
		self.phdr_size = None
		self.phdr_count = None
		self.shdr_size = None
		self.shdr_count = None
		self.shdr_strtable_idx = None

		self.phdrs = None
		self.shdrs = None

	def check(self, f):
		old_offset = f.tell()
		try:
			result = check_file_magic(f, ElfFile64.MAGIC)
		except:
			return False
		finally:
			f.seek(old_offset)
		return result

	def load(self, f):
		data = f.read(struct.calcsize(ElfFile64.FMT))
		if len(data) != struct.calcsize(ElfFile64.FMT):
			print('error: unable to read header')
			return False

		self.magic, self.cls, self.encoding, self.legacy_version, self.os_abi, self.abi_version, self.nident_size, self.type, self.machine, self.version, self.entry, self.phdr_offset, self.shdr_offset, self.flags, self.ehdr_size, self.phdr_size, self.phdr_count, self.shdr_size, self.shdr_count, self.shdr_strtable_idx = struct.unpack(ElfFile64.FMT, data)
		if self.magic != ElfFile64.MAGIC:
			print('error: invalid magic: 0x{0:08X}'.format(self.magic))
			return False
		if self.encoding != ElfFile64.DATA_LSB:
			print('error: unsupported encoding: 0x{0:02X}'.format(self.encoding))
			return False
		if self.legacy_version != ElfFile64.VERSION_CURRENT:
			raise Exception('Unsupported version: 0x{0:x}'.format(self.version))
		if self.cls != ElfFile64.CLASS_64:
			print('error: unsupported class: 0x{0:02X}'.format(self.cls))
			return False
		if not self.type in [ElfFile64.TYPE_EXEC, ElfFile64.TYPE_DYN, ElfFile64.TYPE_SCE_EXEC, ElfFile64.TYPE_SCE_STUB, ElfFile64.TYPE_SCE_EXEC_ASLR, ElfFile64.TYPE_SCE_DYNAMIC]:
			print('error: unsupported type: 0x{0:04X}'.format(self.type))
			return False
		if self.machine != ElfFile64.MACHINE_X86_64:
			print('error: unexpected machine: 0x{0:X}'.format(self.machine))
			return False
		if self.ehdr_size != struct.calcsize(ElfFile64.FMT):
			print('error: invalid elf header size: 0x{0:X}'.format(self.ehdr_size))
			return False
		if self.phdr_size > 0 and self.phdr_size != struct.calcsize(ElfProgramHeader64.FMT):
			print('error: invalid program header size: 0x{0:X}'.format(self.phdr_size))
			return False
		if self.shdr_size > 0 and self.shdr_size != struct.calcsize(ElfSectionHeader64.FMT):
			print('error: invalid section header size: 0x{0:X}'.format(self.shdr_size))
			return False
		if self.shdr_count > 0 and not (0 <= self.shdr_strtable_idx < self.shdr_count):
			print('error: invalid string table section index: {0}'.format(self.shdr_strtable_idx))
			return False

		self.phdrs = []
		for i in xrange(self.phdr_count):
			phdr = ElfProgramHeader64()
			f.seek(self.phdr_offset + i * self.phdr_size)
			if not phdr.load(f):
				print('error: unable to load program header #{0}'.format(i))
				return False
			self.phdrs.append(phdr)

		self.shdrs = []
		if self.shdr_size > 0:
			for i in xrange(self.shdr_count):
				shdr = ElfSectionHeader64()
				f.seek(self.shdr_offset + i * self.shdr_size)
				if not shdr.load(f):
					print('error: unable to load section header #{0}'.format(i))
					return False
				self.shdrs.append(shdr)

			shdr = self.shdrs[self.shdr_strtable_idx]
			if shdr.type != ElfSectionHeader64.SHT_STRTAB:
				print('error: bad section header type for .strtab')
				return False
			f.seek(shdr.offset)
			self.strtable_data = f.read(shdr.size)
			for shdr in self.shdrs:
				shdr.name = self.strtable_data[shdr.name:].split('\0', 1)[0].rstrip('\0')
		else:
			print('error: no section headers')
			return False

		return True

if len(sys.argv) < 2:
	script_file_name = os.path.split(sys.argv[0])[1]
	print('usage: {0} <prx file>'.format(script_file_name))
	sys.exit(0)

prx_file_path = sys.argv[1]
if not os.path.isfile(prx_file_path):
	print('error: invalid prx file specified')
	sys.exit(1)

with open(prx_file_path, 'r+b') as f:
	elf = ElfFile64()
	if not elf.check(f):
		print('error: invalid elf file format')
		sys.exit(1)
	if not elf.load(f):
		print('error: unable to load elf file')
		sys.exit(1)

	scenid_shdr = dynsym_shdr = dynstr_shdr = None
	for shdr in elf.shdrs:
		if shdr.name == '.scenid' and shdr.type == ElfSectionHeader64.SHT_SCENID:
			scenid_shdr = shdr
		elif shdr.name == '.dynsym' and shdr.type == ElfSectionHeader64.SHT_DYNSYM:
			dynsym_shdr = shdr
		elif shdr.name == '.dynstr' and shdr.type == ElfSectionHeader64.SHT_STRTAB:
			dynstr_shdr = shdr

	if scenid_shdr is None:
		print('error: .scenid section header not found')
		sys.exit(1)
	count = scenid_shdr.size // struct.calcsize(ElfNid.FMT)
	if count * struct.calcsize(ElfNid.FMT) != scenid_shdr.size:
		print('error: bad .scenid section size')
		sys.exit(1)
	nids = []
	f.seek(scenid_shdr.offset)
	for i in xrange(count):
		nid = ElfNid()
		if not nid.load(f):
			print('error: unable to load nid #{0}'.format(i))
			sys.exit(1)
		nids.append(nid)

	if dynsym_shdr is None:
		print('error: .dynsym section header not found')
		sys.exit(1)
	count = dynsym_shdr.size // struct.calcsize(ElfSym64.FMT)
	if count * struct.calcsize(ElfSym64.FMT) != dynsym_shdr.size:
		print('error: bad .dynsym section size')
		sys.exit(1)
	symbols = []
	f.seek(dynsym_shdr.offset)
	for i in xrange(count):
		symbol = ElfSym64()
		if not symbol.load(f):
			print('error: unable to load symbol #{0}'.format(i))
			sys.exit(1)
		symbols.append(symbol)

	if dynstr_shdr is None:
		print('error: .dynstr section header not found')
		sys.exit(1)
	f.seek(dynstr_shdr.offset)
	symbol_strtable_data = f.read(dynstr_shdr.size)

	if len(symbols) != len(nids):
		print('error: symbols/nid count mismatch')
		sys.exit(1)

	prefix_regexp = re.compile('^([A-Za-z0-9_]*?)__nid_0x([A-Fa-f0-9]{16})$')

	for i, symbol in enumerate(symbols):
		name = symbol_strtable_data[symbol.name:].split('\0', 1)[0].rstrip('\0')
		if len(name) == 0:
			continue
		file_nid, computed_nid = nids[i].value, calculate_nid(name)
		if file_nid != computed_nid:
			print('error: invalid nid for symbol {0} (was fixed already?)'.format(name))
			sys.exit(1)

	for i, symbol in enumerate(symbols):
		name = symbol_strtable_data[symbol.name:].split('\0', 1)[0].rstrip('\0')
		if len(name) == 0:
			continue
		matches = prefix_regexp.match(name)
		if matches is None:
			continue
		new_name = matches.group(1)
		if len(new_name) == 0:
			new_name = name
		new_nid = int(matches.group(2), 16)
		print('replacing nid for symbol {0}: {1} => 0x{2:016X}'.format(name, new_name, new_nid))
		nids[i].value = new_nid
		new_name = new_name.ljust(len(name), '\0')
		symbol_strtable_data = symbol_strtable_data[:symbol.name] + new_name + symbol_strtable_data[symbol.name + len(new_name):]

	f.seek(dynstr_shdr.offset)
	f.write(symbol_strtable_data)

	f.seek(scenid_shdr.offset)
	for i, nid in enumerate(nids):
		if not nid.save(f):
			print('error: unable to save nid #{0}'.format(i))
			sys.exit(1)
