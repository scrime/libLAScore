#!/usr/bin/env python

import sys

def options(opt):
        opt.load('compiler_cxx')

def configure(conf):
    conf.load('compiler_cxx')
    if sys.platform == 'darwin':
        conf.env.FRAMEWORK_OS = ['LibAudioStream', 'IScore']
    else :
        conf.env.LIB_OS      = ['AudioStream', 'IScore']

    conf.env.INCLUDES = ['.', 'lascore',
                        '/usr/include', '/usr/local/include']
    conf.env.DEFINES  = ['DEBUG(x)=//x']
    conf.env.LIBPATH  = ['.', '/usr/lib', '/usr/local/lib']
    conf.env.LIB      = ['m', 'xml2']
    conf.env.LINKFLAGS= ['-m32']
    conf.env.CXXFLAGS = ['-O3', '-Wall', '-m32']
    
    conf.setenv('debug', env=conf.env.derive())
    conf.env.CXXFLAGS = ['-g', '-Wall', '-m32']
    conf.env.DEFINES  = ['DEBUG(x)=std::cout<< x <<std::endl;']

def build(bld):
    #OpenSoundControl lib
    bld.objects(
        source       = bld.path.ant_glob('src/oscPack/**/*.cpp'),
        target       = 'oscpack',
        use          = ['OS'],
    )
    #Static library
    bld.stlib(
        source       = bld.path.ant_glob('src/*.cpp'),
        target       = 'LAScore'+bld.variant,
        use          = ['oscpack', 'LLVM', 'OS'],
        install_path = '${PREFIX}/lib',
     )
    #Shared library
    bld.shlib(
        source       = bld.path.ant_glob('src/*.cpp'),
        target       = 'LAScore'+bld.variant,
        use          = ['oscpack', 'LLVM', 'OS'],
        install_path = '${PREFIX}/lib',
    )
    #Examples
    bld.program(
        source       = 'examples/simple.cpp',
        target       = 'simple'+bld.variant,
        use          = 'LAScore',
    )

from waflib.Build import BuildContext, CleanContext
class debug(BuildContext):
    cmd = 'debug'
    variant = 'debug'

