# generate equations
#-------------------------------------------------------
#       Procedure: equ_generation
#       Purpose: when equation generation icon is pressed
#-------------------------------------------------------
proc equ_generation {} {
  global ok_flg show_flg init_value func_exp unit iter start interval
  global dep_tbl load_equ_flg
  #
  # call "equ_abs_function" to generate abstract function representations
  # return values: func(i) array -- messages
  #		     
  clear_prev_equ
  set load 0
  set abs_result 1
  if {[equ_exist]} {
    show_equ_found_message
    if {$ok_flg == 1} {
      load_equ
      set load_equ_flg 1
      set load 1
    } else {
      set abs_result [equ_abs_function]
    }
  } else {
    set abs_result [equ_abs_function]
  }

  if {$abs_result == 0} {
    return
  }

  # default values
  if {$load == 0} {
   foreach i [array names func_exp] {
    set init_value($i) { 0 }
    if {$dep_tbl($i) != 0} {
      set show_flg($i) { Yes }
    } else {
      set show_flg($i) { No }
    }
    set unit {iteration}
    set iter {10}
    set start {0}
    set interval {1}
   }
  }

  equ_message_show 
  dpos .bindings
  tkwait visibility .bindings
  grab .bindings
  tkwait window .bindings
}

#-------------------------------------------------------
#       Procedure: clear_prev_equ
#       Purpose: clear all previous equations and expressions
#-------------------------------------------------------
proc clear_prev_equ {} {
  global load_equ_flg exec_equ_flg
  global func_exp abb equ_flg 
  global init_value show_flg unit iter start interval
  global dep_tbl
  global cmd_exp result

  if {$load_equ_flg == 1} {
    set load_equ_flg 0
  }
  if {$exec_equ_flg == 1} {
    unset cmd_exp
    unset result
    set exec_equ_flg 0
  }
}

#-------------------------------------------------------
#       Procedure: equ_exist
#       Purpose: check if the equations are existing in files
#-------------------------------------------------------
proc equ_exist {} {
  global appFileName

  set equ_file_name $appFileName
  set equ_file_name [append equ_file_name {.equ}]
  puts "equ_file_name = $equ_file_name"
  puts "appFileName = $appFileName"
  if {[file exists $equ_file_name]} {
    return 1
  } else {
    return 0
  }
}

#-------------------------------------------------------
#       Procedure: show_equ_found_message
#       Purpose: show the message of preexisting equations
#		 found and ask the user to load or rebuild
#-------------------------------------------------------
proc show_equ_found_message {} {
  global entry_flg

  set msg {"A set of Equations existing in a file. You want to..."}
  set msgarg {-text }
  set msgarg [append msgarg $msg]
  set msgarg [append msgarg { -aspect 650 -justify center}]
  set entry_flg 0
  mkTextWin .modal $msgarg \
    {LOAD {set ok_flg 1}} {REBUILD {set ok_flg 0}}
  dpos .modal
  tkwait visibility .modal
  grab .modal
  tkwait window .modal
}

#-------------------------------------------------------
#       Procedure: load_equ
#       Purpose: load equations from data file
#-------------------------------------------------------
proc load_equ {} {
  global appFileName func_exp abb equ_flg dep_tbl init_value show_flg
  global unit iter start interval

  set firstRead "0"
  set fileName $appFileName 
  set fileName [append fileName {.equ}]
  puts "fileName = $fileName"
  if {[catch "open $fileName r" inFile]} {
    if {!$firstRead} {
      AlertBox "$inFile"
    }
  } else {
    set fileContents [read $inFile]
    close $inFile
    # put data into arrays
    for {set i 0} {$i < [llength $fileContents]} {set i [expr $i+4]} {
      set e1 [lindex $fileContents [expr $i]]
      set abb($e1) [lindex $fileContents [expr $i+2]]
      set func_exp($e1) [lindex $fileContents [expr $i+1]]
      set dep_tbl($e1) [lindex $fileContents [expr $i+3]]
      set equ_flg($e1) 1
      puts "$e1 -- $func_exp($e1) -- abb($e1)"
    }
    puts "length= [llength $fileContents]"
    puts "File contents:\n$fileContents"
  }
  # reading initial values for simulation
  set fileName $appFileName 
  set fileName [append fileName {.init}]
  if {[catch "open $fileName r" inFile]} {
    if {!$firstRead} {
      AlertBox "$inFile"
    }
  } else {
    set fileContents [read $inFile]
    close $inFile
    # put data into arrays
    set unit [lindex $fileContents 0]
    set iter [lindex $fileContents 1]
    set start [lindex $fileContents 2]
    set interval [lindex $fileContents 3]
    for {set i 4} {$i < [llength $fileContents]} {set i [expr $i+3]} {
      set e1 [lindex $fileContents [expr $i]]
      set init_value($e1) [lindex $fileContents [expr $i+1]]
      set show_flg($e1) [lindex $fileContents [expr $i+2]]
      puts "$e1 -- $init_value($e1) -- $show_flg($e1)"
    }
    puts "File contents:\n$fileContents"
  }
}

#-------------------------------------------------------
#       Procedure: equ_message_show
#       Purpose: show messages for equations generation
#-------------------------------------------------------
proc equ_message_show {{w .bindings}} {
  global func_exp abb equ_flg show_flg init_value unit iter start interval
  global dep_tbl first_time

  set complete 1
  foreach i [array names func_exp] {
    set complete [expr $complete*$equ_flg($i)]
  }

  if {$first_time == 1} {
    puts "first time"
    catch {destroy $w}
    toplevel $w
    dpos $w
    set first_time 0
  } else {
    puts "not first time"
    if {$complete != 1} {
      destroy $w.b $w.t1 $w.t2
    } else {
      destroy $w.t1 $w.t2 $w.b
    }
  }

  if {$complete != 1} {
    wm title $w "Equations Generation"
    wm iconname $w "Equations Generation"
  } else {
    wm title $w "Simulation Execution"
    wm iconname $w "Simulation Execution"
  }
  
  if {$complete != 1} {
#    button $w.ok -text OK -command "destroy $w;
    button $w.b -text OK -command "destroy $w;\
	set first_time 1;\
	unset func_exp abb equ_flg show_flg init_value unit iter;\
	unset start interval dep_tbl"
#    pack $w.ok -side bottom -fill x
    pack $w.b -side bottom -fill x
  } else {
    frame $w.b -relief raised -border 1
    pack $w.b -side bottom -fill both -expand yes
    button $w.b.save -text SAVE -command "equ_save"
    button $w.b.exec -text EXECUTION -command "equ_execute"
    button $w.b.quit -text QUIT -command "
	set first_time 1;\
	unset func_exp abb equ_flg show_flg init_value unit iter; \
	unset start interval dep_tbl; \
	destroy $w"
    pack $w.b.save $w.b.exec $w.b.quit -side left -fill both -expand yes
  }
 
  frame $w.t1 -relief raised -border 1
  frame $w.t2 -relief raised -border 1
  pack $w.t1 $w.t2 -side top -fill both -expand yes
  if {$complete != 1} {
    set Height 28
    text $w.t1.b -relief raised -bd 2 -yscrollcommand "$w.t1.s set" \
	    -setgrid true \
            -width 60 -height $Height -borderwidth 3\
	    -font "-Adobe-times-medium-r-normal--*-180*"
    scrollbar $w.t1.s -relief flat -command "$w.t1.b yview"
    pack $w.t1.s -side right -fill y
    pack $w.t1.b -expand yes -fill both
  } else {
    set Height 14
    text $w.t2.b -relief raised -bd 2 -yscrollcommand "$w.t2.s set" \
	    -setgrid true \
            -width 60 -height $Height -borderwidth 3\
	    -font "-Adobe-times-medium-r-normal--*-180*"
    scrollbar $w.t2.s -relief flat -command "$w.t2.b yview"
    pack $w.t2.s -side right -fill y
    pack $w.t2.b -expand yes -fill both
    text $w.t1.b -relief raised -bd 2 -yscrollcommand "$w.t1.s set" \
	    -setgrid true \
            -width 60 -height $Height -borderwidth 3\
	    -font "-Adobe-times-medium-r-normal--*-180*"
    scrollbar $w.t1.s -relief flat -command "$w.t1.b yview"
    pack $w.t1.s -side right -fill y
    pack $w.t1.b -expand yes -fill both
  }
 

  if {[tk colormodel $w] == "color"} {
      set bold "-foreground red"
      set normal "-foreground {}"
  } else {
      set bold "-foreground white -background black"
      set normal "-foreground {} -background {}"
  }

  if {$complete != 1} {
    $w.t1.b insert 0.0 { Based on the flow graph, the following\
 functional dependencies are 
found. }
    $w.t1.b insert end \n\n 
  }

  foreach i [array names func_exp] {
    $w.t1.b insert end {	}
    insertWithTags $w.t1.b $func_exp($i) d$i
    insertWithTags $w.t1.b \n
  }

  if {$complete == 1} {
    $w.t2.b insert end {	Initial value	Displayed on 2D Graph}
    $w.t2.b insert end \n 
    $w.t2.b insert end {_________________________________________}
    $w.t2.b insert end \n 
    foreach i [array names func_exp] {
      $w.t2.b insert end  "$i	  "
      if {$dep_tbl($i) == 0} {
	set cut_pt [string first "=" $func_exp($i)]
        set init_v [string range $func_exp($i) [expr $cut_pt+1] end]
        $w.t2.b insert end  "$init_v"
      } else {
      	insertWithTags $w.t2.b $init_value($i) init$i
      }
      insertWithTags $w.t2.b {		 }
      insertWithTags $w.t2.b $show_flg($i) show$i
      insertWithTags $w.t2.b \n
    }
    $w.t2.b insert end {_________________________________________}
    $w.t2.b insert end \n\n
    insertWithTags $w.t2.b { Unit of Iteration = } 
    insertWithTags $w.t2.b $unit unit_tag
    insertWithTags $w.t2.b \n
    insertWithTags $w.t2.b { Number of Iterations = } 
    insertWithTags $w.t2.b $iter iter_tag
    insertWithTags $w.t2.b \n
    insertWithTags $w.t2.b { Starting Iteration number = } 
    insertWithTags $w.t2.b $start start_tag
    insertWithTags $w.t2.b \n
    insertWithTags $w.t2.b { Interval between Iterations (Unit(s)) = } 
    insertWithTags $w.t2.b $interval interval_tag
    insertWithTags $w.t2.b \n
    foreach i [array names func_exp] {
      set tag init$i
      $w.t2.b tag bind $tag <Any-Enter> "$w.t2.b tag configure $tag $bold"
      $w.t2.b tag bind $tag <Any-Leave> "$w.t2.b tag configure $tag $normal"
      $w.t2.b tag bind init$i <1> "init_input $i"
      set tag show$i
      $w.t2.b tag bind $tag <Any-Enter> "$w.t2.b tag configure $tag $bold"
      $w.t2.b tag bind $tag <Any-Leave> "$w.t2.b tag configure $tag $normal"
      $w.t2.b tag bind show$i <1> "show_input $i"
    }
    set tag unit_tag
    $w.t2.b tag bind $tag <Any-Enter> "$w.t2.b tag configure $tag $bold"
    $w.t2.b tag bind $tag <Any-Leave> "$w.t2.b tag configure $tag $normal"
    # unit
    $w.t2.b tag bind unit_tag <1> "config_input 1"  
    set tag iter_tag
    $w.t2.b tag bind $tag <Any-Enter> "$w.t2.b tag configure $tag $bold"
    $w.t2.b tag bind $tag <Any-Leave> "$w.t2.b tag configure $tag $normal"
    # iter
    $w.t2.b tag bind iter_tag <1> "config_input 2"  
    set tag start_tag
    $w.t2.b tag bind $tag <Any-Enter> "$w.t2.b tag configure $tag $bold"
    $w.t2.b tag bind $tag <Any-Leave> "$w.t2.b tag configure $tag $normal"
    # start
    $w.t2.b tag bind start_tag <1> "config_input 3"   
    set tag interval_tag
    $w.t2.b tag bind $tag <Any-Enter> "$w.t2.b tag configure $tag $bold"
    $w.t2.b tag bind $tag <Any-Leave> "$w.t2.b tag configure $tag $normal"
    # interval
    $w.t2.b tag bind interval_tag <1> "config_input 4"  
  }

  $w.t1.b insert end \n 
  $w.t1.b insert end {where}
  $w.t1.b insert end \n 
  foreach i [array names abb] {
    set msg "	"
    set msg [append msg $i]
    set msg [append msg {: }]
    set msg [append msg $abb($i)]
    $w.t1.b insert end $msg
    $w.t1.b insert end \n 
  }

  if {$complete != 1} {
    $w.t1.b insert end \n 
    $w.t1.b insert end { The user needs to specify actual expressions\
 before executing the 
simulation model. For example, 

	Y(t) = F[ Y(t-1),X,Z ]

The value of Y(t) is derived by calculating the function expression \
which contains three parameters, Y(t-1),X and Z. The specific function \
expression could be 

	Y(t) = ((X-Z)+1)*Y(t-1)

The user is requested to enter such function expression for each abstract \
function expression. }
  } # end if

  foreach i [array names func_exp] {
    set tag d$i
    $w.t1.b tag bind $tag <Any-Enter> "$w.t1.b tag configure $tag $bold"
    $w.t1.b tag bind $tag <Any-Leave> "$w.t1.b tag configure $tag $normal"
    $w.t1.b tag bind d$i <1> "equ_input $i"
  }

  $w.t1.b mark set insert 0.0
  bind $w <Any-Enter> "focus $w.t1.b"
}

#-------------------------------------------------------
#       Procedure: init_input
#       Purpose: input the initial values
#-------------------------------------------------------
proc init_input {abbtext} {
  global init_value input_data ok_flg entry_flg

  set msgarg {-text "Enter Initial Value of }
  set msgarg [append msgarg $abbtext]
  set msgarg [append msgarg {" -aspect 650 -justify left}]
  set input_data $init_value($abbtext)
  set entry_flg 1
  mkTextWin .modal $msgarg \
    {OK {set ok_flg 1}} {Cancel {set ok_flg 0}}
  dpos .modal
  tkwait visibility .modal
  grab .modal
  tkwait window .modal
  if {$ok_flg == 1} {
    set init_value($abbtext) $input_data
    equ_message_show
  } 
}

#-------------------------------------------------------
#       Procedure: config_input
#       Purpose: input the configuration values
#-------------------------------------------------------
proc config_input {case} {
  global unit iter start interval input_data ok_flg entry_flg

  switch -exact -- $case {
	1 {set msg {"Enter UNIT of iteration"}
	   set buffer $unit
	  }
	2 {set msg {"Enter Number of iterations"}
	   set buffer $iter
	  }
	3 {set msg {"Enter Starting Iteration Number"}
	   set buffer $start
	  }
	4 {set msg {"Enter Interval between Iterations (Unit(s))"}
	   set buffer $interval
	  }
  }
  if {[string compare $buffer " ? "] == 0 } {
    set input_data ""
  } else {
    set input_data $buffer
  }
  set msgarg {-text }
  set msgarg [append msgarg $msg]
  set msgarg [append msgarg { -aspect 650 -justify left}]
  set entry_flg 1
  mkTextWin .modal $msgarg \
    {OK {set ok_flg 1}} {Cancel {set ok_flg 0}}
  dpos .modal
  tkwait visibility .modal
  grab .modal
  tkwait window .modal
  if {$ok_flg == 1} {
    switch -exact -- $case {
    	1 {set unit $input_data}
    	2 {set iter $input_data}
    	3 {set start $input_data}
    	4 {set interval $input_data}
    }
    equ_message_show
  }
  set input_data ""
}

#-------------------------------------------------------
#       Procedure: show_input
#       Purpose: input whether show the result (Yes/No)
#-------------------------------------------------------
proc show_input {abbtext} {
  global show_flg 

  puts "result= [string compare $show_flg($abbtext) " No "]"
  if {[string compare $show_flg($abbtext) " No "] == 0 } {
    set show_flg($abbtext) { Yes }
    puts "Match"
  } else {
    set show_flg($abbtext) { No }
  }
  equ_message_show
}

#-------------------------------------------------------
#       Procedure: equ_save
#       Purpose: save the generated equations into files
#-------------------------------------------------------
proc equ_save {} {
  global appFileName func_exp abb dep_tbl show_flg init_value
  global unit iter start interval

  set file_name $appFileName
  set equ_file_name [append file_name {.equ}]
  if {[file exists $equ_file_name]} {
    catch "mv $equ_file_name $equ_file_name~"
  }
  puts "Equ_FileName saving: $equ_file_name"
  if {[catch "open $equ_file_name w" outFile]} {
    AlertBox "$outFile"
  } else {
    # save the equations and fill names indexed by abbreviate name
    foreach i [array names func_exp] {
      puts $outFile "{$i} {$func_exp($i)} {$abb($i)} {$dep_tbl($i)}\n"
    }
    close $outFile
  }
  # save initial values for simulation
  set file_name $appFileName
  set init_file_name [append file_name {.init}]
  if {[file exists $init_file_name]} {
    catch "mv $init_file_name $init_file_name~"
  } 
  if {[catch "open $init_file_name w" outFile]} {
    AlertBox "$outFile"
  } else {
    # save the equations and fill names indexed by abbreviate name
    puts $outFile "{$unit} {$iter} {$start} {$interval}"
    foreach i [array names func_exp] {
      puts $outFile "{$i} {$init_value($i)} {$show_flg($i)}"
    }
    close $outFile
  }
}

#-------------------------------------------------------
#       Procedure: equ_execution
#       Purpose: execute the simulation equations but 
#		 checking the availability first
#-------------------------------------------------------
proc equ_execution {} {
  global ok_flg show_flg init_value func_exp unit iter start interval
  global dep_tbl load_equ_flg
  #
  # call "equ_abs_function" to generate abstract function representations
  # return values: func(i) array -- messages
  #		     
  clear_prev_equ
  set load 0
  set abs_result 1
  if {[equ_exist]} {
    load_equ
    set load_equ_flg 1
    set load 1
  } else {
    set abs_result [equ_abs_function]
  }
  if {$abs_result == 0} {
    return
  }

  # default values
  if {$load == 0} {
   foreach i [array names func_exp] {
    set init_value($i) { 0 }
    if {$dep_tbl($i) != 0} {
      set show_flg($i) { Yes }
    } else {
      set show_flg($i) { No }
    }
    set unit {iteration}
    set iter {10}
    set start {0}
    set interval {1}
   }
  }

  equ_message_show 
  puts "OK"
  dpos .bindings
  tkwait visibility .bindings
  grab .bindings
  tkwait window .bindings
}

#-------------------------------------------------------
#       Procedure: equ_execute
#       Purpose: execute the simulation equations 
#-------------------------------------------------------
proc equ_execute {} {
  global exec_equ_flg

  build_expressions
  execute_expressions
  show_result
#  exec "display.tcl" &
  set exec_equ_flg 1
}

#-------------------------------------------------------
#       Procedure: build_expressions
#       Purpose: build the executable expressions for
#		 the equations
#-------------------------------------------------------
proc build_expressions {} {
  global func_exp cmd_exp

  puts "expressions generated"
  puts "---------------------"
  foreach i [array names func_exp] {
    set cut_pt [string first "=" $func_exp($i)]
    set exp_part [string range $func_exp($i) [expr $cut_pt+1] end]
#    set exp_part [append exp_part { }]
#    puts "$exp_part"
    # cut off (t-1) 
    set find_flg [string first "t-1" $exp_part]
    if {$find_flg != -1} {
      set tmp_part [string range $exp_part 0 [expr $find_flg-2]]
      set tmp_part [append tmp_part [string range $exp_part \
	[expr $find_flg+4] end]]
      set exp_part $tmp_part
    }
#    puts "exp= $exp_part"
    foreach j [array names func_exp] {
      set find_flg [string first $j $exp_part]
      if {$find_flg != -1} {
        set exp_part [replace_var_with_dollar $exp_part $j]
      }
    }
#    puts "exp2= $exp_part"
    set cmd_exp($i) {set }
    set cmd_exp($i) [append cmd_exp($i) $i]
    set cmd_exp($i) [append cmd_exp($i) { [expr }]
    set cmd_exp($i) [append cmd_exp($i) $exp_part]
    set cmd_exp($i) [append cmd_exp($i) {]}]
    puts "$cmd_exp($i)"
  }
}

#-------------------------------------------------------
#       Procedure: replace_var_with_dollar
#       Purpose: for generating expressions, put dollar
#		 sign in front of variables
#-------------------------------------------------------
proc replace_var_with_dollar {exp word} {

  set tmp_part ""
  set part2 $exp
  set wlen [string length $word]
  set find_flg [string first $word $part2]
  while {$find_flg != -1} {
	set tmp_part [append tmp_part \
			[string range $part2 0 [expr $find_flg-1]]]
	set tmp_part [append tmp_part {$}]
	set tmp_part [append tmp_part $word]
	set part2 [string range $part2 [expr $find_flg+$wlen] end]
  	set find_flg [string first $word $part2]
  }
  set tmp_part [append tmp_part $part2]
  return $tmp_part
}

#-------------------------------------------------------
#       Procedure: execute_expressions
#       Purpose: execute the expressions and save the 
#		 results into files
#-------------------------------------------------------
proc execute_expressions {} {
  global cmd_exp unit iter start interval abb dep_tbl
  global init_value show_flg result

  foreach i [array names cmd_exp] {
    set $i $init_value($i)
  }
  puts "num of iter $iter"
  for {set i 1} {$i<=$iter} {incr i} {
    puts "here"
    puts "Interation #$i"
    puts "=============="
    # independent nodes are done first
    foreach j [array names cmd_exp] {
     if {$dep_tbl($j) == 0} {
      if {$i == 1} { 
        set result($j) ""
	lappend result($j) $init_value($j)
      }
      set result_value [eval $cmd_exp($j)]
      puts "$j= $result_value"
      if {[string compare $show_flg($j) " Yes "] == 0 } {
	lappend result($j) $result_value
      }
     }
    }
    # dependent nodes are done followed by independent nodes
    foreach j [array names cmd_exp] {
     if {$dep_tbl($j) != 0} {
      if {$i == 1} { 
        set result($j) ""
	lappend result($j) $init_value($j)
      }
      set result_value [eval $cmd_exp($j)]
      puts "$j= $result_value"
      if {[string compare $show_flg($j) " Yes "] == 0 } {
	lappend result($j) $result_value
      }
     }
    }
  }
  foreach i [array names cmd_exp] {
    if {[string compare $show_flg($i) " Yes "] == 0 } {
      puts "$i"
      puts "================="
      for {set j 0} {$j<=$iter} {incr j} {
        puts "iteration#$j: [lindex $result($i) $j]"
      }
    }
  }
  result_save 
}

#-------------------------------------------------------
#       Procedure: result_save
#       Purpose: save the data of execution results into files
#-------------------------------------------------------
proc result_save {} {
  global abb show_flg unit iter start interval result

  set result_file_name "Simul.Result"
  if {[file exists $result_file_name]} {
    catch "mv $result_file_name $result_file_name~"
  }
  puts "Result_FileName saving: $result_file_name"
  set ct 0
  foreach i [array names show_flg] {
    if {[string compare $show_flg($i) " Yes "] == 0 } {
      set ct [expr $ct+1]
    }
  }
  if {[catch "open $result_file_name w" outFile]} {
    AlertBox "$outFile"
  } else {
    puts $outFile "{$ct}\n"
    close $outFile
  }
  set ct 0
  foreach i [array names show_flg] {
    if {[string compare $show_flg($i) " Yes "] == 0 } {
      set ct [expr $ct+1]
      if {[file exists $result_file_name$ct]} {
    	catch "mv $result_file_name$ct $result_file_name$ct~"
      }
      if {[catch "open $result_file_name$ct w" outFile]} {
    	AlertBox "$outFile"
      } else {
      	#puts "$result($i)"
	set total_iter [llength $result($i)]
      	puts $outFile "{$unit} {$abb($i)}"
      	puts $outFile "{$total_iter} {$start} {$interval}"
      	puts $outFile "{1}"
    	for {set j 0} {$j < $total_iter} {incr j} {
      	  puts $outFile "[lindex $result($i) $j]"
          puts "iteration#$j: [lindex $result($i) $j]"
    	}
    	close $outFile
      }
    }
  }
}


#-------------------------------------------------------
#       Procedure: equ_input
#       Purpose: input equations one by one
#-------------------------------------------------------
proc equ_input {abb_text} {
  global abb func_exp input_data equ_flg ok_flg entry_flg

#  set input_data $abb_text
#  set input_data [append input_data { = }]
  set input_data $func_exp($abb_text)

  set msgarg {-text "}
#  set msgarg [append msgarg $func_exp($abb_text)]
  set msgarg [append msgarg $abb_text]
  set msgarg [append msgarg {: }]
  set msgarg [append msgarg $abb($abb_text)]
  set msgarg [append msgarg {" -aspect 650 -justify left}]
#  puts "--- $msgarg"
  set entry_flg 1
  mkTextWin .modal $msgarg \
    {OK {set ok_flg 1}} {Cancel {set ok_flg 0}}
  dpos .modal
  tkwait visibility .modal
  grab .modal
  tkwait window .modal
  puts "input= $input_data"
  set func_exp($abb_text) $input_data
  if {$ok_flg == 1} {
    set equ_flg($abb_text) 1
    equ_message_show
  }
}

#-------------------------------------------------------
#       Procedure: insertWithTags
#       Purpose: insert tags
#-------------------------------------------------------
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

#-------------------------------------------------------
#       Procedure: equ_abs_function
#       Purpose: equations in abstract function form
#-------------------------------------------------------
proc equ_abs_function {} {
  global obj func_exp abb equ_flg dep_tbl
  # abb : array for mapping abbrev -> text name

  if {[catch "array names obj"]} {
    return 0
  }
  
  foreach i [array names obj] {
    set otype [lindex $obj($i) 1]
    if {$otype >= 1 && $otype <= 4} {
      set text [lindex $obj($i) 4]
      if {[llength $text] == 1} {
        set abb_text [string range $text 0 2]
	set id_abb($i) $abb_text
	set abb($abb_text) $text
	puts "$abb_text : $text"
      } else {
	set abb_text ""
	for {set j 0} {$j < [llength $text]} {incr j} {
	  set subtext [lindex $text $j]
	  set abb_text [append abb_text [string range $subtext 0 0]]
	}
	set id_abb($i) $abb_text
	set abb($abb_text) $text
	puts "$abb_text : $text"
      }
      set equ_flg($abb_text) 0
    }
  }

  foreach i [array names abb] {
    set dep_tbl($i) 0
  }

  foreach i [array names obj] {
    set rel_flg 0
    set otype [lindex $obj($i) 1]
    if {$otype >= 1 && $otype <= 4} {
      set text [lindex $obj($i) 4]
      set abb_text $id_abb($i)
      set func($abb_text) {F[ }
      foreach j [array names obj] {
        set type [lindex $obj($j) 1]
        if {$type == 6} {
	  if {[lindex $obj($j) 4] == $i && $otype ==1 } {
            set rel_flg 1
	    set adj_abb $id_abb([lindex $obj($j) 5])
	    set func($abb_text) [append func($abb_text) $adj_abb]
	    set func($abb_text) [append func($abb_text) {,}]
	    set dep_tbl($abb_text) [expr $dep_tbl($abb_text)+1]
	  } elseif {[lindex $obj($j) 5] == $i && $otype ==1} {
            set rel_flg 1
	    set adj_abb $id_abb([lindex $obj($j) 4])
	    set func($abb_text) [append func($abb_text) $adj_abb]
	    set func($abb_text) [append func($abb_text) {,}]
	    set dep_tbl($abb_text) [expr $dep_tbl($abb_text)+1]
	  }
	} elseif {$type == 7} {
	  if {[lindex $obj($j) 5] == $i} {
	    set adj_abb $id_abb([lindex $obj($j) 4])
            set func($abb_text) [append func($abb_text) $adj_abb]
	    set func($abb_text) [append func($abb_text) {,}]
	    set dep_tbl($abb_text) [expr $dep_tbl($abb_text)+1]
	  }
        }
      }
      if {$rel_flg == 1} {
	set func($abb_text) [append func($abb_text) $abb_text]
	set func($abb_text) [append func($abb_text) {(t-1)}]
	set dep_tbl($abb_text) [expr $dep_tbl($abb_text)+1]
      }
      puts "$abb_text 0 = $func($abb_text)|"
      set len [string length $func($abb_text)]
      set len [expr $len-1]
      set last_char [string range $func($abb_text) $len $len]
      if {[string compare $last_char ","] == 0} {
        puts "last = [string range $func($abb_text) $len $len]"
        puts "$abb_text 1 = $func($abb_text)"
        set func($abb_text) [string range $func($abb_text) 0 [expr $len-1]]
      }
      set func($abb_text) [append func($abb_text) { ]}]
      puts "$abb_text = $func($abb_text)"
      set func_exp($abb_text) ""
      set func_exp($abb_text) [append func_exp($abb_text) $abb_text]
      set func_exp($abb_text) [append func_exp($abb_text) { = }]
      set func_exp($abb_text) [append func_exp($abb_text) $func($abb_text)]
    }
  }
  return 1
}
