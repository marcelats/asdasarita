# when button 1 is press on a certain position of the board
#-------------------------------------------------------
#       Procedure: draw_pos
#       Purpose: draw a node object based on the position
#-------------------------------------------------------
proc draw_pos {w x y} {
  global mode obj_flg input_data

  set input_data ""
  switch -exact -- $mode {
	1 {draw_level $w $x $y}
	2 {draw_rate $w $x $y}
	3 {draw_aux $w $x $y}
	4 {draw_const $w $x $y}
	5 {draw_source $w $x $y}
	6 {draw_link $w $x $y}
	7 {draw_link $w $x $y}
	8 {move_obj $w $x $y}
	9 {delete_pressed $w $x $y}
	10 {edit_text $w $x $y}
  }
}

#-------------------------------------------------------
#       Procedure: draw_level
#       Purpose: draw a level node object 
#-------------------------------------------------------
proc draw_level {w x y} {
  global mode text_data input_data

  set oid [$w create rectangle [expr $x-25] [expr $y-10] [expr $x+25] \
	[expr $y+10] -width 1 ]
  get_text_input $mode
  set text_data $input_data
  add_object $w $oid $mode $x $y $text_data
  set text_data ""
}

#-------------------------------------------------------
#       Procedure: get_text_input
#       Purpose: get text input from the user
#-------------------------------------------------------
proc get_text_input {type} {
  global ok_flg mode entry_flg

  switch -exact -- $type {
	1 {set msg {"Enter Name of Level node"}}
	2 {set msg {"Enter Name of Rate node"}}
	3 {set msg {"Enter Name of Auxiliary node"}}
	4 {set msg {"Enter Name of Constant node"}}
	5 {set msg {"Enter Name of Source/Sink node"}}
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
}

#-------------------------------------------------------
#       Procedure: mkTextWin
#       Purpose: display a focused text input window
#-------------------------------------------------------
proc mkTextWin {w msgArgs args} {
    global input_data entry_flg

    catch {destroy $w}
    toplevel $w -class Dialog
    wm title $w "Input Text"
    wm iconname $w "Dialog"

    frame $w.top -relief raised -border 1
    frame $w.bot -relief raised -border 1
    pack $w.top $w.bot -side top -fill both -expand yes

    eval message $w.top.msg -justify center -width 300\
            -font -Adobe-times-medium-r-normal--*-180* $msgArgs 
#    pack $w.top.msg -side top -expand yes -padx 1 -pady 1

  if {$entry_flg == 1} {
    entry $w.top.e1 -relief sunken -textvariable input_data\
         -scroll "$w.top.s1 set"
    scrollbar $w.top.s1 -relief sunken -orient horiz -command \
            "$w.top.e1 view"
  }

  if {$entry_flg == 1} {
    pack $w.top.msg $w.top.e1 $w.top.s1 -side top \
		-expand yes -fill x
  } else {
    pack $w.top.msg -side top -expand yes -fill x
  }

    if {[llength $args] > 0} {
        focus $w

        set i 0
        foreach arg [lrange $args 0 end] {
            button $w.bot.$i -text [lindex $arg 0] \
            -font -Adobe-times-medium-r-normal--*-180* \
                    -command "[lindex $arg 1]; destroy $w"
            pack $w.bot.$i -side left -expand yes -padx 10 -pady 10
            set i [expr $i+1]
        }
    }
    bind $w <Any-Enter> [list focus $w]
    focus $w
}

#-------------------------------------------------------
#       Procedure: draw_rate
#       Purpose: draw a rate node object 
#-------------------------------------------------------
proc draw_rate {w x y} {
  global mode text_data input_data

  set oid [$w create bitmap $x $y -bitmap @./XBM/rate.bmp ]
  get_text_input $mode
  set text_data $input_data
  add_object $w $oid $mode $x $y $text_data
}

#-------------------------------------------------------
#       Procedure: draw_aux
#       Purpose: draw an auxiliary node object 
#-------------------------------------------------------
proc draw_aux {w x y} {
  global mode text_data input_data

  set oid [$w create oval [expr $x-20] [expr $y-20] [expr $x+20] [expr $y+20] \
      -width 1 ]
  get_text_input $mode
  set text_data $input_data
  add_object $w $oid $mode $x $y $text_data
}

#-------------------------------------------------------
#       Procedure: draw_const
#       Purpose: draw an constant node object 
#-------------------------------------------------------
proc draw_const {w x y} {
  global mode text_data input_data

  set oid [$w create bitmap $x $y -bitmap @./XBM/const.bmp]
  get_text_input $mode
  set text_data $input_data
  add_object $w $oid $mode $x $y $text_data
}

#-------------------------------------------------------
#       Procedure: draw_source
#       Purpose: draw a source/sink node object 
#-------------------------------------------------------
proc draw_source {w x y} {
  global mode text_data input_data

  set oid [$w create bitmap $x $y -bitmap @./XBM/source.bmp]
#  get_text_input $mode
#  set text_data $input_data
  set text_data ""
  add_object $w $oid $mode $x $y $text_data
}

#-------------------------------------------------------
#       Procedure: draw_link
#       Purpose: draw a link object 
#-------------------------------------------------------
proc draw_link {w x y} {
  global mode oid enter_flg selected_id oldx oldy obj link_flg

  set oid [find_obj $x $y]
  if {$oid != -1 && $enter_flg == 1} {
    set otype [lindex $obj($oid) 1]
    if {$otype == 6 || $otype == 7} {
      return
    }
    set selected_id $oid
    set oldx $x
    set oldy $y
    set link_flg 1
  } else {
    set link_flg 0
  }
}

#-------------------------------------------------------
#       Procedure: move_obj
#       Purpose: move an object 
#-------------------------------------------------------
proc move_obj {w x y} {
  global obj selected_id
  global oldx oldy enter_flg

  if {$enter_flg != 1} {
    set selected_id -1
    return
  }
  set oid [find_obj $x $y]
  if {$oid != -1} {
      hide_s_rectangle $w
#      $w delete current
      set selected_id $oid
      puts "moving object# $oid"
      set oldx [lindex $obj($oid) 2]
      set oldy [lindex $obj($oid) 3]
      puts "oldx= $oldx oldy= $oldy"
      $w addtag selected withtag $oid
      set otype [lindex $obj($selected_id) 1]
      if {$otype == 6 || $otype == 7} {
	puts "doing"
	$w delete selected
      } else {
        $w addtag selected withtag [lindex $obj($oid) 5]
      }
  } else {
    set selected_id -1
  }
}

#-------------------------------------------------------
#       Procedure: moving
#       Purpose: while the object is moving
#-------------------------------------------------------
proc moving {w x y} {
  global oldx oldy
  global obj mode selected_id new_link_id link_flg

  if {$selected_id != -1} {
    # moving an object 
    if {$mode == 8} {
      set x [$w canvasx $x]
      set y [$w canvasy $y]
      set otype [lindex $obj($selected_id) 1]
      if {$otype == 6 || $otype == 7} {
        $w delete selected
	set sid [lindex $obj($selected_id) 4]
	set tid [lindex $obj($selected_id) 5]
	set sx [lindex $obj($sid) 2]
	set sy [lindex $obj($sid) 3]
	set tx [lindex $obj($tid) 2]
	set ty [lindex $obj($tid) 3]
	set direction [find_direction $sx $sy $tx $ty]
        set stype [lindex $obj($sid) 1]
        set ttype [lindex $obj($tid) 1]
        set pos_data [find_xy $direction $stype $sx $sy $ttype $tx $ty $otype]
        set sx [lindex $pos_data 0]
        set sy [lindex $pos_data 1]
        set tx [lindex $pos_data 2]
        set ty [lindex $pos_data 3]

        if {$otype == 6} {
	  if {$ttype == 2} {
            set s_id [$w create line $sx $sy $x $y $tx $ty -width 1 \
		-smooth true]
	  } else {
            set s_id [$w create line $sx $sy $x $y $tx $ty -width 1 \
		-smooth true -arrow last]
	  }
        } else {
          set s_id [$w create line $sx $sy $x $y $tx $ty -width 1 -arrow last \
	    -smooth true -capstyle projecting -stipple @./bitmaps/grey.5 ]
        }
	set new_link_id $s_id
        $w addtag selected withtag $s_id
      } else {
        $w move selected [expr $x-$oldx] [expr $y-$oldy]
      }
      set oldx $x
      set oldy $y
    # creating a link 
    } elseif {$mode == 6 || $mode == 7} {
      if {$link_flg == 0} {
	return
      }
      set x [$w canvasx $x]
      set y [$w canvasy $y]
      $w delete selected
      if {$mode == 6} {
        set s_id [$w create line $oldx $oldy $x $y -width 1 -arrow last]
      } else {
        set s_id [$w create line $oldx $oldy $x $y -width 1 -arrow last \
	    -capstyle projecting -stipple @./bitmaps/grey.5 ]
      }
      $w addtag selected withtag $s_id
    }
  }
}

#-------------------------------------------------------
#       Procedure: move_end 
#       Purpose: while the moving is ended
#-------------------------------------------------------
proc move_end {w x y} {
  global selected_id obj mode oldx oldy new_link_id link_flg
 
  if {$selected_id != -1} {
    puts "move end"
    # moving an object 
    if {$mode == 8} {
      set x [$w canvasx $x]
      set y [$w canvasy $y]
      set obj($selected_id) [lreplace $obj($selected_id) 2 3 $x $y]
      set otype [lindex $obj($selected_id) 1]
      if {$otype == 6 || $otype == 7} {
	change_link_id $selected_id $new_link_id
#        set obj($new_link_id) [lreplace $obj($selected_id) 0 0 $new_link_id]
#	puts "obj($selected_id)= $obj($selected_id)"
#	puts "obj($new_link_id)= $obj($new_link_id)"
#	unset obj($selected_id)
#	puts "obj# $selected_id is changed as obj# $new_link_id"
      } else {
        puts "obj# $selected_id moved = $obj($selected_id)"
	move_asso_links $w
      }
      $w dtag selected
      $w delete label
      show_s_rectangle $w
    } elseif {$mode == 6 || $mode == 7} {  # draw a link 
      if {$link_flg == 0} {
	return
      }
      set x [$w canvasx $x]
      set y [$w canvasy $y]
      set t_id [find_obj $x $y]
	puts "t_id = $t_id"
      $w delete selected
      if {$t_id != -1} {
	# draw an accurate link
        set direction [find_direction $oldx $oldy $x $y]
        set stype [lindex $obj($selected_id) 1]
  	set ttype [lindex $obj($t_id) 1]
  	set pos_data [find_xy $direction $stype $oldx $oldy $ttype $x $y $mode]
	set oldx [lindex $pos_data 0]
  	set oldy [lindex $pos_data 1]
  	set x [lindex $pos_data 2]
  	set y [lindex $pos_data 3]

	if {$mode == 6} {
	  if {$ttype == 2} {
      	    set oid [$w create line $oldx $oldy $x $y -width 1]
    	  } else {
            set oid [$w create line $oldx $oldy $x $y -width 1 -arrow last]
	  }
	} else {
          set oid [$w create line $oldx $oldy $x $y -width 1 -arrow last \
	    -capstyle projecting -stipple @./bitmaps/grey.5 ]
	}
        add_link $w $oid $mode [expr ($oldx+$x)/2] [expr ($oldy+$y)/2] \
		$selected_id $t_id
	hide_s_rectangle $w
	show_s_rectangle $w
      }
    }
  }
}

#-------------------------------------------------------
#       Procedure: delete_pressed
#       Purpose: button 1 is pressed in delete mode
#-------------------------------------------------------
proc delete_pressed {w x y} {
#  puts "deleted object type= [$w type current]"
  delete_obj $w $x $y
}

#-------------------------------------------------------
#       Procedure: delete_obj
#       Purpose: delete an object 
#-------------------------------------------------------
proc delete_obj {w x y} {
  global obj enter_flg

  set oid [find_obj $x $y]
  if {$oid != -1 && $enter_flg ==1} {
#    $w delete current
    puts "deleting object# $oid"
    $w delete $oid
    set otype [lindex $obj($oid) 1]
    if {$otype >= 1 && $otype <=5 } {
      delete_asso_links $w $oid
      $w delete [lindex $obj($oid) 5]
    }
    unset obj($oid)
    $w delete label
    show_s_rectangle $w
  }
}

#-------------------------------------------------------
#       Procedure: edit_text
#       Purpose: modify the text of node
#-------------------------------------------------------
proc edit_text {w x y} {
  global obj enter_flg text_data ok_flg input_data

  set oid [find_obj $x $y]
  if {$oid != -1 && $enter_flg ==1} {
    puts "edit text on object# $oid"
    set otype [lindex $obj($oid) 1]
    if {$otype >= 1 && $otype <=5 } {
#      set text_data [lindex $obj($oid) 4]
      set input_data [lindex $obj($oid) 4]
      get_text_input [lindex $obj($oid) 1]
      set text_data $input_data 
      if {$ok_flg == 1} {
	set obj($oid) [lreplace $obj($oid) 4 4 $text_data]
	$w delete [lindex $obj($oid) 5]
	set tx_id [show_text $w $otype $x $y $text_data]
	set obj($oid) [lreplace $obj($oid) 5 5 $tx_id]
      }
      set text_data ""
    }
  }
}

#-------------------------------------------------------
#       Procedure: find_obj
#       Purpose: check if an object can be found
#-------------------------------------------------------
proc find_obj {x y} {
  global obj enter_flg obj_flg

  if {$obj_flg == 0} {
    return 
  }
  foreach i [array names obj] {
    set ox [lindex $obj($i) 2]
    set oy [lindex $obj($i) 3]
    if { abs([expr $ox-$x]) <= 3 && abs([expr $oy-$y]) <= 3} {
      return [lindex $obj($i) 0]
    } 
  }
  return -1
}

#-------------------------------------------------------
#       Procedure: add_object
#       Purpose: add an object in the object group
#-------------------------------------------------------
proc add_object {w oid otype x y text} {
  global obj  obj_flg

  puts "input_text_data= $text"
  set tx_id [show_text $w $otype $x $y $text]
  set obj($oid) [list $oid $otype $x $y $text $tx_id]
  puts "object# $oid added => $obj($oid)"
  $w addtag object withtag $oid
  set obj_flg 1
}

#-------------------------------------------------------
#       Procedure: show_text
#       Purpose: show the text part of a node
#-------------------------------------------------------
proc show_text {w otype x y text} {
  global obj

  if {$otype == 1 || $otype == 4} {
    return [$w create text $x [expr $y-20] -text $text]
  } else {
    return [$w create text $x [expr $y-30] -text $text]
  }
}

#-------------------------------------------------------
#       Procedure: add_link
#       Purpose: add a link object into the object group
#-------------------------------------------------------
proc add_link {w oid otype x y s_id t_id} {
  global obj 

  set obj($oid) [list $oid $otype $x $y $s_id $t_id]
  puts "object# $oid added => $obj($oid)"
  $w addtag object withtag $oid
}

#-------------------------------------------------------
#       Procedure: change_link_id
#       Purpose: when a link is moved, change a new link id
#-------------------------------------------------------
proc change_link_id {old_id new_id} {
  global obj

  set obj($new_id) [lreplace $obj($old_id) 0 0 $new_id]
  puts "obj($old_id)= $obj($old_id)"
  puts "obj($new_id)= $obj($new_id)"
  unset obj($old_id)
  puts "obj# $old_id is changed as obj# $new_id"
}

#-------------------------------------------------------
#       Procedure: move_asso_links
#       Purpose: when an object is moved, all associated
#		 links are moved 
#-------------------------------------------------------
proc move_asso_links {w} {
  global selected_id obj

  $w delete label
  foreach i [array names obj] {
    set otype [lindex $obj($i) 1]
    if {$otype == 6 || $otype == 7} {
      set sid [lindex $obj($i) 4]
      set tid [lindex $obj($i) 5]
      if {$sid == $selected_id || $tid == $selected_id} {
	$w addtag del_tag withtag $i
	$w delete del_tag
        set sx [lindex $obj($sid) 2]
        set sy [lindex $obj($sid) 3]
        set x [lindex $obj($i) 2]
        set y [lindex $obj($i) 3]
        set tx [lindex $obj($tid) 2]
        set ty [lindex $obj($tid) 3]
	set direction [find_direction $sx $sy $tx $ty]
        set stype [lindex $obj($sid) 1]
        set ttype [lindex $obj($tid) 1]
        set pos_data [find_xy $direction $stype $sx $sy $ttype $tx $ty $otype]
        set sx [lindex $pos_data 0]
        set sy [lindex $pos_data 1]
        set tx [lindex $pos_data 2]
        set ty [lindex $pos_data 3]

        if {$otype == 6} {
	  if {$ttype == 2} {
            set s_id [$w create line $sx $sy $x $y $tx $ty -width 1 \
		-smooth true]
	  } else {
            set s_id [$w create line $sx $sy $x $y $tx $ty -width 1 \
                -smooth true -arrow last]
	  }
        } else {
          set s_id [$w create line $sx $sy $x $y $tx $ty -width 1 -arrow last \
            -smooth true -capstyle projecting -stipple @./bitmaps/grey.5 ]
        }
        $w addtag object withtag $s_id
	change_link_id $i $s_id
      }
    }
  }
  show_s_rectangle $w
}

#-------------------------------------------------------
#       Procedure: delete_asso_links
#       Purpose: when a node object is deleted, all 
#		 associated links should be removed.
#-------------------------------------------------------
proc delete_asso_links {w oid} {
  global obj

  $w delete label
  foreach i [array names obj] {
    set otype [lindex $obj($i) 1]
    if {$otype == 6 || $otype == 7} {
      set sid [lindex $obj($i) 4]
      set tid [lindex $obj($i) 5]
      if {$sid == $oid || $tid == $oid} {
	$w addtag del_tag withtag $i
	$w delete del_tag
	unset obj($i)
      }
    }
  }
  show_s_rectangle $w
}

#-------------------------------------------------------
#       Procedure: update_pos
#       Purpose: update the mouse position (X,Y)
#-------------------------------------------------------
proc update_pos {w x y} {
  catch {destroy .menu.position}

  set x [$w canvasx $x]
  set y [$w canvasy $y]
  label .menu.position -text "X:$x Y:$y" -relief raised
  pack .menu.fname .menu.position -side right
}

#-------------------------------------------------------
#       Procedure: grid_select
#       Purpose: in grid mode, button 1 is pressed
#-------------------------------------------------------
proc grid_select {} {
  global grid_mode

  show_grid_selection
  tkwait visibility .grid
  grab .grid
  tkwait window .grid
  change_grid_mode
}

#-------------------------------------------------------
#       Procedure: show_grid_selection
#       Purpose: show grid selection window and ask
#		 the user's input
#-------------------------------------------------------
proc show_grid_selection {{w .grid}} {
  global grid_mode

    catch {destroy $w}
    toplevel $w -class Dialog
    wm title $w "Mode Selection"
    wm iconname $w "Dialog"

    frame $w.top -relief raised -border 1
    frame $w.bot -relief raised -border 1
    pack $w.top $w.bot -side top -fill both -expand yes

    message $w.top.msg -text "Grid Mode" -justify center -width 300\
            -font -Adobe-times-medium-r-normal--*-180*  
    pack $w.top.msg

    button $w.bot.s0 -bitmap @./XBM/grid0.bmp -command {destroy .grid
				set grid_mode 0}
    button $w.bot.s1 -bitmap @./XBM/grid1.bmp -command {destroy .grid
				set grid_mode 1} 
    button $w.bot.s2 -bitmap @./XBM/grid2.bmp -command {destroy .grid
				set grid_mode 2} 
    button $w.bot.sc -bitmap @./XBM/cancel.bmp -command {destroy .grid
				return -1} 
    pack $w.bot.s0 $w.bot.s1 $w.bot.s2 $w.bot.sc -side left

}

#-------------------------------------------------------
#       Procedure: change_grid_mode
#       Purpose: change grid mode
#-------------------------------------------------------
proc change_grid_mode {} {
  global grid_mode

  catch {destroy .plate.left.b14}
  puts "grid_mode = $grid_mode"
  switch -exact -- $grid_mode {
        0 {button .plate.left.b14 -bitmap @./XBM/grid0.xbm -padx 16 \
		-command "grid_select"
	  }
        1 {button .plate.left.b14 -bitmap @./XBM/grid1.xbm -padx 16 \
		-command "grid_select"
	  }
        2 {button .plate.left.b14 -bitmap @./XBM/grid2.xbm -padx 16 \
		-command "grid_select"
	  }
  }
  pack .plate.left.b1 .plate.left.b2 .plate.left.b3 .plate.left.b4 \
        .plate.left.b5 .plate.left.b6 .plate.left.b7 .plate.left.b8 \
        .plate.left.b9 .plate.left.b10 .plate.left.b12 \
        .plate.left.b13 .plate.left.b14 -side top -expand yes
  bind .plate.left.b14 <2> {incr_grid_mode}
  bind .plate.left.b14 <3> {decr_grid_mode}
  switch -exact -- $grid_mode {
	0 {show_grid 0}
	1 {show_grid 1}
	2 {show_grid 2}
  }
}

#-------------------------------------------------------
#       Procedure: incr_grid_mode
#       Purpose: in grid mode, when button 2 is pressed
#-------------------------------------------------------
proc incr_grid_mode {} {
  global grid_mode 

  set grid_mode [expr ($grid_mode+1)%3]
  change_grid_mode
#  show_grid $grid_mode
}

#-------------------------------------------------------
#       Procedure: decr_grid_mode
#       Purpose: in grid mode, when button 3 is pressed
#-------------------------------------------------------
proc decr_grid_mode {} {
  global grid_mode 

  set grid_mode [expr ($grid_mode-1)%3]
  change_grid_mode
#  show_grid $grid_mode
}

#-------------------------------------------------------
#       Procedure: show_grid
#       Purpose: show grid on the canvas
#-------------------------------------------------------
proc show_grid {mode {w .plate.right.board}} {
  set max_x 1417
  set max_y 1417
  set dp 10
  $w delete grid_tag

  if {$mode != 0} {
    if {$mode == 1} {
      set step 40
    } else {
      set step 20
    }
    for {set x 0} {$x <= $max_x} {set x [expr $x+$step]} {
       set oid [$w create line $x 0 $x $max_y -width 1 \
            -stipple @./bitmaps/grey.05 ]
       $w addtag grid_tag withtag $oid
    }
    for {set y 0} {$y <= $max_y} {set y [expr $y+$step]} {
       set oid [$w create line 0 $y $max_x $y -width 1 \
            -stipple @./bitmaps/grey.05 ]
       $w addtag grid_tag withtag $oid
    }
  }
}
