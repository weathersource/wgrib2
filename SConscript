#!python

import os

# The cleaning code was borrowed from https://bitbucket.org/scons/scons/wiki/CustomCleanActions
def TestClean(env, targets):

    if not env.GetOption('clean'):
        return False

    # Normalize targets to absolute paths
    targets = env.subst('${TARGETS.abspath}', target=targets).split()
    launchDir = env.GetLaunchDir()
    topDir = env.Dir("#").abspath
    clTargets = COMMAND_LINE_TARGETS

    if len(clTargets) == 0:
        clTargets.append(".")

    for i in range(len(clTargets)):
        
        fullTarget = ""

        if clTargets[i][0] == '#':
            fullTarget = os.path.join(topDir,clTargets[i][1:0])
        else:
            fullTarget = os.path.join(launchDir,clTargets[i])

        fullTarget = os.path.normpath(fullTarget)

        for target in targets:
            if target.startswith(fullTarget):
                return True

    return False

def CleanActionFunc(env, targets, action):
    if TestClean(env, targets):
        env.Execute(action)

# The name of our program
TARGET='wgrib2'

# This is the way to make sure that environment variables are passed
# to the "make" command that is called downstream
env = Environment( ENV = { 'CC': 'gcc', 'FC': 'gfortran', 'PATH': os.environ['PATH'] } )

# Add the cleaner to the environment
env.AddMethod(CleanActionFunc, 'CleanAction')

# Get the commmand line prefix and add it to the environment
vars = Variables()
vars.Add( PathVariable( 'PREFIX', 'Installation Prefix', '/usr/local', PathVariable.PathIsDirCreate ) ) 
vars.Update(env)

installDir = env['PREFIX']

t = env.Command( "src/wgrib2/" + TARGET, "", "cd src && make" )
Default( t )

# Override the default clean to redirect it to call "make clean"
env.CleanAction( t, Action(['cd src && make clean']) )

# Add an installer
binTarget = os.path.join( installDir, 'bin' )
env.Install( binTarget, t )
env.Alias( 'install', binTarget )
