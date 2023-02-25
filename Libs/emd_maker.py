#!/usr/bin/env python

import sys, os, re

if len(sys.argv) < 2:
	script_file_name = os.path.split(sys.argv[0])[1]
	print('usage: {0} <def file>'.format(script_file_name))
	sys.exit(0)

desc_file_path = sys.argv[1]
if not os.path.isfile(desc_file_path):
	print('error: invalid definition file specified: {0}'.format(desc_file_path))
	sys.exit(1)

desc_file_path_wo_ext = os.path.splitext(desc_file_path)[0]
lib_name = os.path.split(desc_file_path_wo_ext)[1]

fun_names = []
obj_names = []
tls_names = []

with open(desc_file_path, 'r') as f:
	marker = None
	marker_regexp = re.compile(r'^([A-Za-z0-9_]+)\s*:$', re.IGNORECASE)
	name_with_nid_regexp = re.compile(r'^([A-Za-z0-9_]+)\s*=\s*(0[xX][A-Fa-f0-9]+)\s*$')
	for line in f.readlines():
		line = line.rstrip('\r\n').strip()
		if len(line) == 0:
			continue
		if line.startswith(';'):
			continue
		matches = marker_regexp.match(line)
		if matches is not None:
			marker = matches.group(1)
			continue
		matches = name_with_nid_regexp.match(line)
		if matches is not None:
			name, nid = matches.group(1), matches.group(2)
			line = '{0}__nid_{1}'.format(name, nid)
		if marker == 'fun':
			fun_names.append(line)
		elif marker == 'obj':
			obj_names.append(line)
		elif marker == 'tls':
			tls_names.append(line)

asm_file_path = desc_file_path_wo_ext + '.S'
if os.path.isfile(asm_file_path):
	os.remove(asm_file_path)

with open(asm_file_path, 'w') as f:
	for i, name in enumerate(fun_names):
		f.write('.global {0}\n.type {0}, @function\n{0}:\n\tretq\n\n'.format(name))
	f.write('\n')
	for i, name in enumerate(obj_names):
		f.write('.global {0}\n.type {0}, @object\n{0}:\n\t.byte 0\n\n'.format(name))

c_file_path = desc_file_path_wo_ext + '.c'
if os.path.isfile(c_file_path):
	os.remove(c_file_path)

with open(c_file_path, 'w') as f:
	#for i, name in enumerate(fun_names):
	#	f.write('__declspec(dllexport) void* {0}() {{}}\n'.format(name))
	#f.write('\n')
	#for i, name in enumerate(obj_names):
	#	f.write('__declspec(dllexport) char {0};\n'.format(name))
	#f.write('\n')
	for i, name in enumerate(tls_names):
		f.write('__thread char {0}[1];\n'.format(name))

emd_file_path = desc_file_path_wo_ext + '.emd'
if os.path.isfile(emd_file_path):
	os.remove(emd_file_path)

with open(emd_file_path, 'w') as f:
	f.write('Library: {0} {{\n\texport: {{\n'.format(lib_name))
	for i, name in enumerate(fun_names):
		f.write('\t\t{0}\n'.format(name))
	for i, name in enumerate(obj_names):
		f.write('\t\t{0}\n'.format(name))
	for i, name in enumerate(tls_names):
		f.write('\t\t{0}\n'.format(name))
	f.write('\t}\n}\n')
