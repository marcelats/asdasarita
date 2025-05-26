       @echo off
       if not "%1" == "" goto APPLE
       echo.
       echo Oops -- command line parameter 1 is missing!
       echo The parameter selects version of cpudisk to translate:
       echo.
       echo   1 = essentially original simpack code, using sim++ cAPI
       echo   2 = c++ version using ooAPI
       echo   3 = 2 above + event routines
       echo   4 = 3 above + events characterized by event_routine vs event_id
       echo   5 = 4 above + semiautomatic style (atomic occurrence/execution)
       echo   6 = 4 above + automatic style (atomic occurrence/execution)
       echo.
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
       echo Try again.  This time specify a parameter in range 1..6.
       echo.
       goto ZEBRA
:BERRY
       if "%1" == "1" goto CHARD
       if "%1" == "2" goto CHARD
       if "%1" == "3" goto CHARD
       if "%1" == "4" goto CHARD
       if "%1" == "5" goto CHARD
       if "%1" == "6" goto CHARD
       echo No unnerstan.
       echo.
       echo Try again.  This time specify a parameter in range 1..6.
       echo.
       goto ZEBRA
:CHARD
       copy cpudisk%1 cpudisk.cpp
       tcc @..\compile.rsp cpudisk.cpp
       tcc cpudisk.obj @..\link.rsp
       del cpudisk.obj
:ZEBRA

