# help for introduction
proc help_intro {{w .basic}} {
  catch {destroy $w}
  toplevel $w
  dpos $w
  wm title $w "Introduction"
  button $w.ok -text OK -command "destroy $w"
  text $w.t -relief raised -bd 2 -yscrollcommand "$w.s set" -setgrid true\
            -width 73 -height 16 \
            -font "-Adobe-Helvetica-bold-R-Normal-*-140-*"        
  scrollbar $w.s -relief flat -command "$w.t yview"
  pack $w.ok -side bottom -fill x
  pack $w.s -side right -fill y
  pack $w.t -expand yes -fill both 
    $w.t tag configure bold -font -Adobe-Courier-Bold-O-Normal-*-120-*
    $w.t tag configure big -font -Adobe-Courier-Bold-R-Normal-*-140-*
    $w.t tag configure verybig -font -Adobe-Helvetica-Bold-R-Normal-*-240-*
    if {[tk colormodel $w] == "color"} {
        $w.t tag configure color1 -background #eed5b7
        $w.t tag configure color2 -foreground red
        $w.t tag configure color3 -foreground blue
        $w.t tag configure raised -background #eed5b7 -relief raised \
                -borderwidth 1
        $w.t tag configure sunken -background #eed5b7 -relief sunken \
                -borderwidth 1
    } else {
        $w.t tag configure color1 -background black -foreground white
        $w.t tag configure color2 -background black -foreground white
        $w.t tag configure raised -background white -relief raised \
                -borderwidth 1
        $w.t tag configure sunken -background white -relief sunken \
                -borderwidth 1
    }
    $w.t tag configure bgstipple -background black -borderwidth 0 \
            -bgstipple gray25
    $w.t tag configure fgstipple -fgstipple gray50
    $w.t tag configure underline -underline on

  $w.t insert 0.0 {\
  This Help is intended to describe the usage of the }
  insertWithTags $w.t {System Dynamics
Simulation Modeling Tools} color2 
  insertWithTags $w.t { (SDSMT) } color3
  insertWithTags $w.t {and help the user to do simulation using
system dynamics approach. The }
  insertWithTags $w.t {SDSMT } color3 
  insertWithTags $w.t {is a userfriendly graphical interface
completely developed by using Tk/Tcl scripting language. Generally, the }
  insertWithTags $w.t {SDSMT } color3 
  insertWithTags $w.t {
can be introduced by dividing its functions to three portions, they are: }
  insertWithTags $w.t { Systeme 
Dynamics(SD) graph editor, equation generation, simulation execution and
result displayer.} color2 
  insertWithTags $w.t {

  The first part, }
  insertWithTags $w.t {system dynamics graph editor} color2
  insertWithTags $w.t {, is a graphical user interface 
allowing the user to edit }
  insertWithTags $w.t {system dynamics graphs. } color2 
  insertWithTags $w.t {Several editing icon buttons
facilitate the graph editing, including the creation of }
  insertWithTags $w.t {level, rate, auxiliary, constant
 and source/sink nodes. } color3 
  insertWithTags $w.t {In addition, the user is allowed to modify the graph by}
  insertWithTags $w.t {
moving, deleting and text-changing } color3
  insertWithTags $w.t {functions. Once a system dynamics graph is }
  insertWithTags $w.t {
completed,} color2 
  insertWithTags $w.t { the user can} 
insertWithTags $w.t { save } color3 
insertWithTags $w.t {it into the file using the name that he/she prefers and 
load it back later on.

  The second part is about the generation of }
  insertWithTags $w.t {differential equations } color2 
  insertWithTags $w.t {for the currently 
editing system dynamics graph. When a system dynamics graph is }
  insertWithTags $w.t {finished} color2 
  insertWithTags $w.t {, a set 
of abstract equations representing the relationships between /among the nodes 
on the graph are }
  insertWithTags $w.t {generated } color2 
  insertWithTags $w.t {by the software. The user needs to input the }
  insertWithTags $w.t {expressions } color2 
  insertWithTags $w.t {to complete the equations before the simulation execution. Once all equations
are modified, the system directly goes to the third part, }
  insertWithTags $w.t {simulation execution.} color2 
  insertWithTags $w.t {

  The last part, }
  insertWithTags $w.t {simulation execution module} color2 
  insertWithTags $w.t {, is based on the equations input by
the user to generate a set of executable codes. To directly execute a pre-existing
system dynamics model, the user can press the }
  insertWithTags $w.t {"simulation execution" } color3 
  insertWithTags $w.t {icon.  }
  insertWithTags $w.t {The
other way } color2 
  insertWithTags $w.t {to enter the simulation execution window is }
  insertWithTags $w.t {after completing } color2
  insertWithTags $w.t {the input 
of }
  insertWithTags $w.t {differential equations. } color2 
  insertWithTags $w.t {When the simulation execution window shows up, the user
is still allowed to modify the equations and input some required initial values. 
Once the required data are completed, the user can start the execution by 
pressing }
  insertWithTags $w.t {"execution" } color3 
  insertWithTags $w.t {button. After a short execution time, depending on the 
number of simulation iterations, the }
   insertWithTags $w.t {simulation result window } color2
   insertWithTags $w.t {is poped up and allow
user to make selections of displaying }
   insertWithTags $w.t {all individual results } color2 
   insertWithTags $w.t {or }
   insertWithTags $w.t {a single graph } color2
   insertWithTags $w.t {
containing all results on }
    insertWithTags $w.t {2D graphs.} color2

}

# help for flow graph
proc help_flow_graph {{w1 .basic}} {
  catch {destroy $w1}
  toplevel $w1
  dpos $w1
  wm title $w1 "Create Flow Graph"
  button $w1.ok -text OK -command "destroy $w1"
  text $w1.t -relief raised -bd 2 -yscrollcommand "$w1.s set" -setgrid true\
            -width 70 -height 16 \
            -font "-Adobe-Helvetica-bold-R-Normal-*-140-*"
  scrollbar $w1.s -relief flat -command "$w1.t yview"
  pack $w1.ok -side bottom -fill x
  pack $w1.s -side right -fill y
  pack $w1.t -expand yes -fill both
    $w1.t tag configure bold -font -Adobe-Courier-Bold-O-Normal-*-120-*
    $w1.t tag configure big -font -Adobe-Courier-Bold-R-Normal-*-140-*
    $w1.t tag configure verybig -font -Adobe-Helvetica-Bold-R-Normal-*-240-*
    if {[tk colormodel $w1] == "color"} {
        $w1.t tag configure color1 -background #eed5b7
        $w1.t tag configure color2 -foreground red
        $w1.t tag configure color3 -foreground blue
        $w1.t tag configure raised -background #eed5b7 -relief raised \
                -borderwidth 1
        $w1.t tag configure sunken -background #eed5b7 -relief sunken \
                -borderwidth 1
    } else {
        $w1.t tag configure color1 -background black -foreground white
        $w1.t tag configure color2 -background black -foreground white
        $w1.t tag configure raised -background white -relief raised \
                -borderwidth 1
        $w1.t tag configure sunken -background white -relief sunken \
                -borderwidth 1
    }
    $w1.t tag configure bgstipple -background black -borderwidth 0 \
            -bgstipple gray25
    $w1.t tag configure fgstipple -fgstipple gray50
    $w1.t tag configure underline -underline on

  $w1.t insert 0.0 {\
  The Flow Graph symbols are the bottons in the left side of the window. The
ten bottons from LEVEL to EDIT are devoted to help user to design the Flow
Garph.
}
  insertWithTags $w1.t {
 The following four bottons work in the same way. They are:}
  insertWithTags $w1.t {
 LEVEL, RATE, AUX, CONSTANT 
} color2
  insertWithTags $w1.t {
 Step1: } color3
  insertWithTags $w1.t {\
    Click the icon you want to draw using the first button of mouse.
}
  insertWithTags $w1.t {\
   Step2: } color3
  insertWithTags $w1.t {\
    Click the position you want the icon to placed in the right board.              
}  
  insertWithTags $w1.t {\
   Step3: } color3
  insertWithTags $w1.t {\
    As you placing the icon, name the icon in the dialog window.
}

  insertWithTags $w1.t {\
   Step4: } color3
  insertWithTags $w1.t {\
    If you want to move the icon, click the mouse third button, then 
              using the mouse second button to drag it to the position you want.
}
  insertWithTags $w1.t {
 SOURCE / SINK
} color2
  insertWithTags $w1.t {
 Step1: } color3
  insertWithTags $w1.t {\
    Click the icon you want to draw using the first button of mouse.
}
  insertWithTags $w1.t {\
   Step2: } color3
  insertWithTags $w1.t {\
    Click the position you want the icon to placed in the right board.
}
  insertWithTags $w1.t {\
   Step3: } color3
  insertWithTags $w1.t {\
    If you want to move the icon, click the mouse third button, then
              using the mouse second button to drag it to the position you want
}
  insertWithTags $w1.t {
 FLOW / C.E. LINK
} color2
  insertWithTags $w1.t {
  Step1: } color3
  insertWithTags $w1.t {\
    Before you use these two icons, you should have drawed some of above
               icons since they are for helping buliding the relations between the 
               LEVEL, RATES, AUX, CONSTANT and SOURCE/SINK.
}
  insertWithTags $w1.t {
  Step2: } color3
  insertWithTags $w1.t {\
    Click the two icons you want to draw using the first button of mouse.
}
  insertWithTags $w1.t {
  Step3: } color3
  insertWithTags $w1.t {\
    Click the first icon you want to make a link, and drag to the other icon
               you want it to be linked. The system will detected wheather your linking 
               is reasonable or not, if it it, the link will display, if it isn't. the link will 
               be canceled.
}
  insertWithTags $w1.t {
 MOVE
} color2
  insertWithTags $w1.t {
  Step1: } color3
  insertWithTags $w1.t {\
    This button act as same as the third mouse button; as you click it, you
              can move the icons in the right board. If you change the position of the 
              LEVEL, RATES, AUX, CONSTANT ,SOURCE/SINK icons, their link will 
              also change according their position.
}
  insertWithTags $w1.t {
 DELETE
} color2
  insertWithTags $w1.t {
   Step1: } color3
  insertWithTags $w1.t {\
    Click the DELETE icon using the first button of mouse.
}
  insertWithTags $w1.t {  \
     Step2: } color3
  insertWithTags $w1.t {\
    Click the little box in the object you want to delete using the first 
                button of mouse.
}
  insertWithTags $w1.t {
 EDIT
} color2
  insertWithTags $w1.t {
   Step1: } color3
  insertWithTags $w1.t {\
    Click the EDIT icon using the first button of mouse.
}
 insertWithTags $w1.t {  \
     Step2: } color3
  insertWithTags $w1.t {\
    Click the little box in the object you want to edit using the first
                button of mouse.
}
 insertWithTags $w1.t {  \
   Step3: } color3
  insertWithTags $w1.t {\
    Enter the new text you want to change to the pop up dialog window.    
}
  insertWithTags $w1.t {
 Grid Mode
} color2
  insertWithTags $w1.t {
   Step1: } color3
  insertWithTags $w1.t {\
    Click the Grid Mode button using the mouse first button.
}
 insertWithTags $w1.t {  \
     Step2: } color3
  insertWithTags $w1.t {\
    Select the grid mode density showing by the pop up window.
                }
   insertWithTags $w1.t {Or } underline
   insertWithTags $w1.t {\
                 click the Grid Mode button again using the mouse second button. 
                 If you keep clicking it, it will show you the different grid density.
                }
   insertWithTags $w1.t {Or } underline
   insertWithTags $w1.t {\
                 you can click the Grid Mode button using the mouse third button;
                 As you keep click it, it will also disply the different grid density,
                 but the density order is opposite from you click it with the mouse 
                 second button. 
}
  $w1.t mark set insert 0.0
  bind $w1 <Any-Enter> "focus $w1.t"
}


# help for equation generations
proc help_equ {{w .basic}} {
  catch {destroy $w}
  toplevel $w
  dpos $w
  wm title $w "Equation Generation"
  button $w.ok -text OK -command "destroy $w"
  text $w.t -relief raised -bd 2 -yscrollcommand "$w.s set" -setgrid true\
            -width 72 -height 16 \
            -font "-Adobe-Helvetica-bold-R-Normal-*-140-*"
  scrollbar $w.s -relief flat -command "$w.t yview"
  pack $w.ok -side bottom -fill x
  pack $w.s -side right -fill y
  pack $w.t -expand yes -fill both
    $w.t tag configure bold -font -Adobe-Courier-Bold-O-Normal-*-120-*
    $w.t tag configure big -font -Adobe-Courier-Bold-R-Normal-*-140-*
    $w.t tag configure verybig -font -Adobe-Helvetica-Bold-R-Normal-*-240-*
    if {[tk colormodel $w] == "color"} {
        $w.t tag configure color1 -background #eed5b7
        $w.t tag configure color2 -foreground red
        $w.t tag configure raised -background #eed5b7 -relief raised \
                -borderwidth 1
        $w.t tag configure sunken -background #eed5b7 -relief sunken \
                -borderwidth 1
    } else {
        $w.t tag configure color1 -background black -foreground white
        $w.t tag configure color2 -background black -foreground white
        $w.t tag configure raised -background white -relief raised \
                -borderwidth 1
        $w.t tag configure sunken -background white -relief sunken \
                -borderwidth 1
    }
    $w.t tag configure bgstipple -background black -borderwidth 0 \
            -bgstipple gray25
    $w.t tag configure fgstipple -fgstipple gray50
    $w.t tag configure underline -underline on

  $w.t insert 0.0 {\
  To create }
 insertWithTags $w.t {Equation Generation} color2
 insertWithTags $w.t 	{, just select the Equation Generation button
  in the left side. After you click it, a }
 insertWithTags $w.t {pop-up window } color2 
 insertWithTags $w.t {will display the
  default equations. User can edit or input the corresponding equations
  based on the current }
  insertWithTags $w.t {Flow Graph.} color2 
  insertWithTags $w.t { 

  If the current Flow Graph are }
   insertWithTags $w.t {reloaded} color2
   insertWithTags $w.t { and not the new one, the system will
  check if there is an }
   insertWithTags $w.t {old} color2
   insertWithTags $w.t { equation file exists; if there is one, the system will
  ask if you want to load the old equation file as you click the equation button. 

  To input or edit the equation, just move your mouse in the pop-up window,
  as the variable }
   insertWithTags $w.t {change its color} color2
   insertWithTags $w.t {, click the variable and enter the data into 
   the dialog box, click the OK button to exit the dialog box. After finishing
   editing/inputing, you should find the equations have been updated.

  As long as you }
  insertWithTags $w.t {complete } color2
  insertWithTags $w.t {the modification of the equations, the system will
  pop-up a }
  insertWithTags $w.t {initial value input window.} color2 
  insertWithTags $w.t { This window help you to input the 
  initial values for the following simulation. For futher information about the
  window, please see the help of }
  insertWithTags $w.t {simulation equation button} color2 
  insertWithTags $w.t {.

  You should}
  insertWithTags $w.t { make sure} color2
  insertWithTags $w.t { all the equations are }
  insertWithTags $w.t {correct} color2
  insertWithTags $w.t {, otherwise, }
  insertWithTags $w.t {errors } color2 
  insertWithTags $w.t {might 
  happen during running the simulation.  } 
  $w.t mark set insert 0.0
  bind $w <Any-Enter> "focus $w.t"

}

# help for simulation execution
proc help_exec {{w1 .basic}} {
  catch {destroy $w1}
  toplevel $w1
  dpos $w1
  wm title $w1 "Create Flow Graph"
  button $w1.ok -text OK -command "destroy $w1"
  text $w1.t -relief raised -bd 2 -yscrollcommand "$w1.s set" -setgrid true\
            -width 70 -height 16 \
            -font "-Adobe-Helvetica-bold-R-Normal-*-140-*"
  scrollbar $w1.s -relief flat -command "$w1.t yview"
  pack $w1.ok -side bottom -fill x
  pack $w1.s -side right -fill y
  pack $w1.t -expand yes -fill both
    $w1.t tag configure bold -font -Adobe-Courier-Bold-O-Normal-*-120-*
    $w1.t tag configure big -font -Adobe-Courier-Bold-R-Normal-*-140-*
    $w1.t tag configure verybig -font -Adobe-Helvetica-Bold-R-Normal-*-240-*
    if {[tk colormodel $w1] == "color"} {
        $w1.t tag configure color1 -background #eed5b7
        $w1.t tag configure color2 -foreground red
        $w1.t tag configure color3 -foreground blue
        $w1.t tag configure raised -background #eed5b7 -relief raised \
                -borderwidth 1
        $w1.t tag configure sunken -background #eed5b7 -relief sunken \
                -borderwidth 1
    } else {
        $w1.t tag configure color1 -background black -foreground white
        $w1.t tag configure color2 -background black -foreground white
        $w1.t tag configure raised -background white -relief raised \
                -borderwidth 1
        $w1.t tag configure sunken -background white -relief sunken \
                -borderwidth 1
    }
    $w1.t tag configure bgstipple -background black -borderwidth 0 \
            -bgstipple gray25
    $w1.t tag configure fgstipple -fgstipple gray50
    $w1.t tag configure underline -underline on
    $w1.t insert 0.0 {\
   Before executing the model, you should make sure there exists a equation file

}
 insertWithTags $w1.t {*Please see the help of equation generation to create the equatione file.} color3
  insertWithTags $w1.t {

  To execute the model, click the }
  insertWithTags $w1.t {Simulation Execution} color2
  insertWithTags $w1.t { Button. Once the button
  is clicked, the system will load the equation file of the }
  insertWithTags $w1.t {current Flow Graph} color2
  insertWithTags $w1.t {
  automatically. If the equation file is not found,the system will pop up a equation 
  generation window to ask you to create one. If there is one, a }
  insertWithTags $w1.t {Simulation 
  Execution } color2
  insertWithTags $w1.t {window will be poped up.

  In the Simulation Execution window, you can see the equation window and the
  initial value window at the same time. You still can }
  insertWithTags $w1.t {modify } color2
  insertWithTags $w1.t {the equations in the
  equation generation window. However, for the simulation execution, you still 
  need to input the initial values for the variables in the initial value window. All 
  the default initial values are zeros.

  To edit the initial values just move the mouse to the corresponding }
  insertWithTags $w1.t {initial value. } color2
  insertWithTags $w1.t { After the value change its color,  click it and input the new data to the dialog
  edit box, click OK to exit the dialog box, then you can see the new initial value has been updated.

  If you want to save the current equations and the current initial values,you
  can select the }
  insertWithTags $w1.t {SAVE} color2
  insertWithTags $w1.t { button in the bottom line of the window. It will generated
  a new equation file and a initial value file for the current Flow Graph.

  As all the initial value setting finished, you can execute the model by clicking
  the }
  insertWithTags $w1.t {EXECUTION } color2 
  insertWithTags $w1.t {button in the bottom line. After the simulation execution 
  completed, a execution result window will be pop up in the }
  insertWithTags $w1.t {upper right side } color2
  insertWithTags $w1.t {
  screen. There are two ways to display the final results:

  }
  insertWithTags $w1.t {One} color2 
  insertWithTags $w1.t { is to show the results }
  insertWithTags $w1.t {seperately } color2 
  insertWithTags $w1.t {by clicking the }
  insertWithTags $w1.t {Show individual} color2 
  insertWithTags $w1.t { result
  button; }
  insertWithTags $w1.t {

  The other } color2 
  insertWithTags $w1.t {is to show }
  insertWithTags $w1.t {all } color2
  insertWithTags $w1.t {the results in the same graph by clicking the }
  insertWithTags $w1.t {Show all } color2 
  insertWithTags $w1.t {
  button.}

  insertWithTags $w1.t {
  
  To exit the 2-D result graphs, click the Quit button to return to the initial value 
  window.}
 
  $w1.t mark set insert 0.0
  bind $w1 <Any-Enter> "focus $w1.t"


}

proc insertWithTags {w text args} {
    set start [$w index insert]
    $w insert insert $text
    foreach tag [$w tag names $start] {
        $w tag remove $tag $start insert
    }
    foreach i $args {
        $w tag add $i $start insert
    }
}
