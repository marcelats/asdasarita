       @echo off
       set src=iterate
       if not "%1" == "" goto APPLE
       echo.
       echo Oops -- command line parameter 1 is missing!
       echo The parameter selects version to of %src% translate:
       echo   1 = cAPI version
       echo   2 = ooAPI version
       echo Try again.  This time specify a parameter as above.
       echo.
       goto ZEBRA
:APPLE
       if not "%1" == "0" goto BERRY
       echo.
       echo   Version 0 does not exist.  There was no simpack version.
       echo.
       echo Try again.  This time specify a parameter in range 1..2.
       echo.
       goto ZEBRA
:BERRY
       if "%1" == "1" goto CHARD
       if "%1" == "2" goto CHARD
       echo No unnerstan.
       echo.
       echo Try again.  This time specify a parameter in range 1..2.
       echo.
       goto ZEBRA
:CHARD
       copy %src%%1 %src%.cpp
       tcc @..\compile.rsp %src%.cpp
       tcc %src%.obj @..\link.rsp
       del %src%.obj
:ZEBRA
       set src=

