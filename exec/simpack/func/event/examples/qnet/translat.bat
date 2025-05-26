       @echo off
       set src=qnet
       if not "%1" == "" goto APPLE
       echo.
       echo Oops -- command line parameter 1 is missing!
       echo The parameter selects version to of %src% translate:
       echo   1 = essentially original simpack code, using sim++ cAPI
       echo Try again.  This time specify a parameter as above.
       echo.
       goto ZEBRA
:APPLE
       if not "%1" == "0" goto BERRY
       echo.
       echo   Version 0 is not compilable.  It is the simpack version, and is
       echo   present only so you can compare it with version 1, to see what
       echo   had to be changed to run under sim++.
       echo.
       echo Try again.  This time specify a parameter in range 1..1.
       echo.
       goto ZEBRA
:BERRY
       if "%1" == "1" goto CHARD
       echo No unnerstan.
       echo.
       echo Try again.  This time specify a parameter in range 1..1.
       echo.
       goto ZEBRA
:CHARD
       copy %src%%1 %src%.cpp
       tcc @..\compile.rsp %src%.cpp
       tcc %src%.obj @..\link.rsp
       del %src%.obj
:ZEBRA
       set src=

