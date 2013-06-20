#!/usr/bin/env python

import sys

def options(opt):
        opt.load('compiler_cxx')

def configure(conf):
        conf.load('compiler_cxx')
        if sys.platform == 'darwin':
            conf.env.FRAMEWORK_LOOPER = ['Cocoa','OpenGL','AGL']


def build(bld):
    bld.objects(
        source       = bld.path.ant_glob('src/oscPack/**/*.cpp'),
        target       = 'oscpack',
        includes     = ['/usr/include','/usr/local/include'],
        cxxflags     = ['-w','-m32'],
    )

    #Static library
    bld.stlib(
        source       = bld.path.ant_glob('src/*.cpp'),
        use          = ['oscpack','LLVM'],
        target       = 'LAScore',
        includes     = ['.', '/usr/include', '/usr/local/include'],
        lib          = ['m'],
        libpath      = ['/usr/lib','/usr/local/lib'],
        linkflags    = ['-m32'],
        framework   = ['LibAudioStream', 'IScore'],
        vnum         = '0.0.1',
        install_path = '${PREFIX}/lib',
        cxxflags     = ['-O3', '-Wall', '-m32']
     )

    #Shared library
    bld.shlib(
        source       = bld.path.ant_glob('src/*.cpp'),
        use          = ['oscpack','LLVM'],
        target       = 'LAScore',
        includes     = ['.', '/usr/include', '/usr/local/include'],
        lib          = ['m'],
        libpath      = ['/usr/lib','/usr/local/lib'],
        linkflags    = ['-m32'],
        framework   = ['LibAudioStream', 'IScore'],
        vnum         = '0.0.1',
        install_path = '${PREFIX}/lib',
        cxxflags     = ['-O3', '-Wall', '-m32']
    )

    #Examples
    bld.program(
        source       = 'examples/simple.cpp',
        use          = 'LAScore',
        target       = 'simple',
        includes     = ['.', '/usr/include', '/usr/local/include'],
        cxxflags     = ['-O3', '-Wall', '-m32'],
        lib          = ['m'],
        linkflags    = ['-m32'],
        framework   = ['LibAudioStream', 'IScore'],
        libpath      = ['/usr/lib', '/usr/local/lib', '.'],
    )

