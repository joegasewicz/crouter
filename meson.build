project('crouter', 'c',
        version : '1.0.0',
        default_options : ['warning_level=3', 'c_std=c11'])

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_MESON_LIBRARY']

python_dep = dependency('python3', modules:['Python'], required: true)

python_inc = include_directories('/opt/homebrew/Cellar/python@3.14/3.14.0/Frameworks/Python.framework/Versions/3.14/include/python3.14')

shared_library('crouter', 'crouter.c',
       install : true,
       c_args : lib_args,
       include_directories: python_inc,
       link_args: ['-F/opt/homebrew/Cellar/python@3.14/3.14.0/Frameworks', '-framework', 'Python'],
       dependencies: python_dep,
)



#cython_build = custom_target(
#    'cython_build',
#    output: '_router.cython-*.so',
#    command: ['python3', 'setup.py', 'build_ext', '--inplace'],
#    depend_files: ['crouter/crouter.pyx', 'crouter.c', 'crouter.h'],
#    build_by_default: true
#)