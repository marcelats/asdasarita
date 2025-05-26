       @echo off
       set src=ssq
       if not "%1" == "" goto APPLE
       echo.
       echo Oops -- command line parameter 1 is missing!
       echo The parameter selects version to of %src% translate:
       echo   1 = essentially original simpack code, using sim++ cAPI,
       echo       baseline version, no snapshots
       echo   2 = version 1 + snapshots at every event, BATCH mode, with simulation
       echo       exit time reduced from 1000 to 5, to limit quantity of output
       echo   3 = same as version 2 except INTERACTIVE mode
       echo   4 = same as versions 2 & 3, except selective snapshots instead of
       echo       snapshot at every event
       echo   5 = baseline c++ version using ooAPI, no snapshots
       echo       manual simulation style
       echo   6 = baseline c++ version using ooAPI, no snapshots,
       echo       semiautomatic simulation style
       echo   7 = baseline c++ version using ooAPI, no snapshots,
       echo       automatic simulation style
       echo   8 = 7 above + snapshots after every event, BATCH mode
       echo   9 = same as 8, except INTERACTIVE mode
       echo  10 = same as 9, except idle facilities are NOT displayed
       echo  11 = same as 10, except BATCH mode, suitable for redirection to a file
       echo  12 = 7 above + selective snapshots
       echo  13 = 7 above + automatic snapshots over brief time interval
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
       echo Try again.  This time specify a parameter in range 1..13.
       echo.
       goto ZEBRA
:BERRY
       if "%1" == "1" goto CHARD
       if "%1" == "2" goto CHARD
       if "%1" == "3" goto CHARD
       if "%1" == "4" goto CHARD
       if "%1" == "5" goto CHARD
       if "%1" == "6" goto CHARD
       if "%1" == "7" goto CHARD
       if "%1" == "8" goto CHARD
       if "%1" == "9" goto CHARD
       if "%1" == "10" goto CHARD
       if "%1" == "11" goto CHARD
       if "%1" == "12" goto CHARD
       if "%1" == "13" goto CHARD
       echo No unnerstan.
       echo.
       echo Try again.  This time specify a parameter in range 1..12.
       echo.
       goto ZEBRA
:CHARD
       copy %src%%1 %src%.cpp
       tcc @..\compile.rsp %src%.cpp
       tcc %src%.obj @..\link.rsp
       del %src%.obj
:ZEBRA
       set src=

