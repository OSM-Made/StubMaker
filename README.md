# StubMaker
Windows port of flatz ps4_stub_lib_maker.

# Credits
Credits to flats for the original project https://github.com/flatz/ps4_stub_lib_maker_v2 

# Build Instructions

1. Requires Official SDK :( so you must specify your SDK path in ``Libs/makeStub.bat``.
2. Run the ``build.bat``.
3. All of the generated stubs will be in the root of the repo.
4. You can now link against these stubs with more function definitions than the official.

# Build Requirements
- Python 2.7
- Sony PS4 SDK

# Installing Python 2.7 using miniconda on Windows 11a

1. Download and install Miniconda: You can download Miniconda from the [offical website](https://docs.conda.io/projects/miniconda/en/latest/)
2. During the installation process, you'll be prompted to select environment variables. Choose the following options:
    - Add Miniconda3 to my PATH environment variable
    - Register Miniconda3 as my default Python 3.11
    - Clear the package cache upon completion 

3. Verify the Conda version by running `conda --version`
in your terminal.

4. Create a Python 2.7 environment named "py27" with the command: `conda create --name py27`

5. Start the Conda environment in terminal by running `conda init powershell` 

6. Restart your terminal to ensure that the changes take effect.

7. Check the list of Conda environments using the command: `conda env list`

8. Activate the Python 2.7 environment you created with: `conda activate py27`

9. Install Python 2.7 in your "py27" environment using the command: `conda install python=2.7.18`
