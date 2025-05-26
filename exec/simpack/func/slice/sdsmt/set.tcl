# called when level mode is selected
#-------------------------------------------------------
#       Procedure: set_level
#       Purpose: set mode to be level mode
#-------------------------------------------------------
proc set_level {w} { 
  global mode

  set mode 1
  hide_s_rectangle $w
}
  
#-------------------------------------------------------
#       Procedure: set_rate
#       Purpose: set mode to be rate mode
#-------------------------------------------------------
proc set_rate {w} {
  global mode

  set mode 2
  hide_s_rectangle $w
}
  
#-------------------------------------------------------
#       Procedure: set_aux
#       Purpose: set mode to be auxiliary mode
#-------------------------------------------------------
proc set_aux {w} {
  global mode

  set mode 3
  hide_s_rectangle $w
}
  
#-------------------------------------------------------
#       Procedure: set_const
#       Purpose: set mode to be constant mode
#-------------------------------------------------------
proc set_const {w} {
  global mode

  set mode 4
  hide_s_rectangle $w
}
  
#-------------------------------------------------------
#       Procedure: set_source
#       Purpose: set mode to be source/sink mode
#-------------------------------------------------------
proc set_source {w} {
  global mode

  set mode 5
  hide_s_rectangle $w
}
  
#-------------------------------------------------------
#       Procedure: set_flow
#       Purpose: set mode to be flow link mode
#-------------------------------------------------------
proc set_flow {w} {
  global mode

  set mode 6
  show_s_rectangle $w
}
  
#-------------------------------------------------------
#       Procedure: set_celink
#       Purpose: set mode to be CE link mode
#-------------------------------------------------------
proc set_celink {w} {
  global mode

  set mode 7
  show_s_rectangle $w
}
  
#-------------------------------------------------------
#       Procedure: set_move
#       Purpose: set mode to be move mode
#-------------------------------------------------------
proc set_move {w} {
  global mode

  set mode 8
  show_objects $w
  show_s_rectangle $w
  # show small squares
}

#-------------------------------------------------------
#       Procedure: set_delete
#       Purpose: set mode to be delete mode
#-------------------------------------------------------
proc set_delete {w} {
  global mode

  set mode 9
  show_objects $w
  show_s_rectangle $w
  # show small squares
}

#-------------------------------------------------------
#       Procedure: set_edit
#       Purpose: set mode to be text editing mode
#-------------------------------------------------------
proc set_edit {w} {
  global mode

  set mode 10
  show_objects $w
  show_s_rectangle $w
  # show small squares
}

#-------------------------------------------------------
#       Procedure: show_objects
#       Purpose: show info about objects
#-------------------------------------------------------
proc show_objects {w} {
  global mode obj obj_flg

  if {$obj_flg == 0} {
    return
  }
  puts "---- List objects -----"
  foreach i [array names obj] {
    puts "object# $i = $obj($i)"
  }
  puts "\n"
}

#-------------------------------------------------------
#       Procedure: show_s_rectangle
#       Purpose: show object labels (small rectangles)
#-------------------------------------------------------
proc show_s_rectangle {w} {
  global mode obj obj_flg label_flg

  if {$obj_flg == 0} {
    return
  }
  set label_flg 1
  foreach i [array names obj] {
    set x [lindex $obj($i) 2]
    set y [lindex $obj($i) 3]
    set sid [$w create rectangle [expr $x-3] [expr $y-3] [expr $x+3] \
        [expr $y+3] -width 1 ]
    $w addtag label withtag $sid
  }
}

#-------------------------------------------------------
#       Procedure: hide_s_rectangle
#       Purpose: hide object labels (small rectangles)
#-------------------------------------------------------
proc hide_s_rectangle {w} {
  global label_flg

  set label_flg 0
  $w delete label
#  $w dtag label
}

#-------------------------------------------------------
#       Procedure: set_enter
#       Purpose: set enter_flag to be true
#-------------------------------------------------------
proc set_enter {w} {
  global enter_flg

  $w itemconfig current -fill Red
  set enter_flg 1
}

#-------------------------------------------------------
#       Procedure: set_leave
#       Purpose: set enter_flag to be false
#-------------------------------------------------------
proc set_leave {w} {
  global enter_flg

#  $w itemconfig current -fill SkyBlue2
  $w itemconfig current -fill ""
  set enter_flg 0
}
