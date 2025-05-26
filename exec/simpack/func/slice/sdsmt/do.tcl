#-------------------------------------------------------
#	Procedure: do_new
#	Purpose: clear the canvas and reset the file name
#-------------------------------------------------------
proc do_new {} {
  global appFileName

  delete_all
  set appFileName "unnamed.sdg"
  show_file_name
}

#-------------------------------------------------------
#	Procedure: do_load
#	Purpose: load a system dynamics graph from a
#		 file and display it.
#-------------------------------------------------------
proc do_load {} {
  global appFileName obj_flg abb func_exp

  set selFile [file_window "Load File"]
#  puts "FileName: $selFile"
  if {"$selFile" != ""} {
    set appFileName $selFile
    set read_res [Read_File $appFileName]
    puts "read_res= $read_res"
    if {$read_res} {
     show_file_name
#    clear_prev_equ
#    if {$obj_flg == 1} {
#      unset abb
#      unset func_exp
#    }
     set obj_flg 1
    }
  } 
}

#-------------------------------------------------------
#	Procedure: Read_File
#	Purpose: check if read operation is successful.
#-------------------------------------------------------
proc Read_File {fileName {firstRead "0"}} {

  if {[catch "open $fileName r" inFile]} {
    if {!$firstRead} {
      AlertBox "$inFile"
    }
  } else {
    if {[catch "read $inFile" fileContents]} {
      puts "Error dsd"
      return 0
    } else {
      puts "Correct"
#      set fileContents [read $inFile]
      close $inFile
      display_object $fileContents
      return 1
#     puts "File contents:\n$fileContents"
    }
  }
}

#-------------------------------------------------------
#	Procedure: display_object
#	Purpose: Display the SD graph objects on the canvas.
#-------------------------------------------------------
proc display_object {Contents} {
  global obj

  set w .plate.right.board
  delete_all
  puts [llength $Contents]
  set num_obj [expr [llength $Contents]/6]
  for {set i 0} {$i < $num_obj} {incr i} {
    set oid [lindex $Contents [expr 6*$i]]
    set otype [lindex $Contents [expr 6*$i+1]]
    set x [lindex $Contents [expr 6*$i+2]]
    set y [lindex $Contents [expr 6*$i+3]]
    if {$otype >=1 && $otype <= 5} {
      set text_data [lindex $Contents [expr 6*$i+4]]
      set new_id [redraw_object $w $otype $x $y $text_data]
      set id_map($oid) $new_id
    } else {
      set sid [lindex $Contents [expr 6*$i+4]]
      set tid [lindex $Contents [expr 6*$i+5]]
      redraw_link $w $otype $x $y $id_map($sid) $id_map($tid)
    }
  }
}

#-------------------------------------------------------
#	Procedure: redraw_object
#	Purpose: redraw objects on the canvas.
#-------------------------------------------------------
proc redraw_object {w type x y text} {
  global obj

  switch -exact -- $type {
  	1 {set oid [$w create rectangle [expr $x-25] [expr $y-10] [expr $x+25]\
        	[expr $y+10] -width 1 ]}
	2 {set oid [$w create bitmap $x $y -bitmap @./XBM/rate.bmp ]}
	3 {set oid [$w create oval [expr $x-20] [expr $y-20] [expr $x+20]\
		[expr $y+20] -width 1 ]}
	4 {set oid [$w create bitmap $x $y -bitmap @./XBM/const.bmp]}
	5 {set oid [$w create bitmap $x $y -bitmap @./XBM/source.bmp]}
  }
  set text_id [show_text $w $type $x $y $text]
  set obj($oid) [list $oid $type $x $y $text $text_id]
  puts "object #$oid loaded: $obj($oid)"
  return $oid
}

#-------------------------------------------------------
#	Procedure: redraw_link
#	Purpose: redraw the links between objects on the canvas.
#-------------------------------------------------------
proc redraw_link {w type x y sid tid} {
  global obj

  puts "object #$sid (source) : $obj($sid)"
  puts "object #$tid (target) : $obj($tid)"
  set sx [lindex $obj($sid) 2]
  set sy [lindex $obj($sid) 3]
  set tx [lindex $obj($tid) 2]
  set ty [lindex $obj($tid) 3]
  set direction [find_direction $sx $sy $tx $ty]
  set stype [lindex $obj($sid) 1]
  set ttype [lindex $obj($tid) 1]
  set pos_data [find_xy $direction $stype $sx $sy $ttype $tx $ty $type]
  puts "pos= $pos_data"
  set sx [lindex $pos_data 0]
  set sy [lindex $pos_data 1]
  set tx [lindex $pos_data 2]
  set ty [lindex $pos_data 3]
  if {$type == 6} {
    if {$ttype == 2} {
      set oid [$w create line $sx $sy $x $y $tx $ty -width 1 -smooth true]
    } else {
      set oid [$w create line $sx $sy $x $y $tx $ty -width 1 \
         -smooth true -arrow last]
    }
  } else {
    set oid [$w create line $sx $sy $x $y $tx $ty -width 1 -arrow last \
      -smooth true -capstyle projecting -stipple @./bitmaps/grey.5 ]
  }
  set obj($oid) [list $oid $type $x $y $sid $tid]
  puts "link object $oid: $obj($oid) loaded"
}

#-------------------------------------------------------
#	Procedure: find_xy 
#	Purpose: find proper X,Y coordinates to draw a link.
#-------------------------------------------------------
proc find_xy {direction stype sx sy ttype tx ty {otype 1}} {
  if {$direction == 1} {  # to the right 
    switch -exact -- $stype {
	1 {set sx [expr $sx+25]}
	2 {set sx [expr $sx+14]}
	3 {set sx [expr $sx+20]}
	5 {set sx [expr $sx+24]}
    }
    switch -exact -- $ttype {
	1 {set tx [expr $tx-25]}
	2 {if {$otype == 7} {
	     set ty [expr $ty+19]
	   } else {
	     set tx [expr $tx-14]
	   }
	  }
	3 {set tx [expr $tx-20]}
	5 {set tx [expr $tx-20]}
    }
  } elseif {$direction == 2} {  # to the top
    switch -exact -- $stype {
	1 {set sy [expr $sy-10]}
	2 {set sy [expr $sy-19]}
	3 {set sy [expr $sy-20]}
	5 {set sy [expr $sy-25]}
    }
    switch -exact -- $ttype {
	1 {set ty [expr $ty+10]}
	2 {set ty [expr $ty+19]}
	3 {set ty [expr $ty+20]}
	5 {set ty [expr $ty+23]}
    }
  } elseif {$direction == 3} {  # to the left
    switch -exact -- $stype {
	1 {set sx [expr $sx-25]}
	2 {set sx [expr $sx-14]}
	3 {set sx [expr $sx-20]}
	5 {set sx [expr $sx-20]}
    }
    switch -exact -- $ttype {
	1 {set tx [expr $tx+25]}
	2 {if {$otype == 7} {
	     set ty [expr $ty+19]
	   } else {
	     set tx [expr $tx+14]
 	   }
          }
	3 {set tx [expr $tx+20]}
	5 {set tx [expr $tx+24]}
    }
  } elseif {$direction == 4} {  # to the bottom
    switch -exact -- $stype {
	1 {set sy [expr $sy+10]}
	2 {set sy [expr $sy+19]}
	3 {set sy [expr $sy+20]}
	5 {set sy [expr $sy+23]}
    }
    switch -exact -- $ttype {
	1 {set ty [expr $ty-10]}
	2 {set ty [expr $ty-19]}
	3 {set ty [expr $ty-20]}
	5 {set ty [expr $ty-25]}
    }
  }
  return [list $sx $sy $tx $ty]
}

#-------------------------------------------------------
#	Procedure: find_direction 
#	Purpose: find direction vector from one object to
#		 the other.
#-------------------------------------------------------
proc find_direction {sx sy tx ty} {

  if {$sx < $tx} {  # target is on the right
    if {abs([expr $ty-$sy]) <= [expr $tx-$sx]} {
      set direction 1
    } else {
      if {[expr $ty-$sy] > 0 } {
        set direction 4
      } else {
        set direction 2
      }
    }
  } elseif {$sx > $tx} { # target is on the left
    if {abs([expr $ty-$sy]) <= [expr $sx-$tx]} {
      set direction 3
    } else {
      if {[expr $ty-$sy] > 0 } {
        set direction 4
      } else {
        set direction 2
      }
    }
  } else { # target is either on the top and bottom
    if {[expr $ty-$sy] > 0 } {
      set direction 4
    } else {
      set direction 2
    }
  }
  return $direction
}

#-------------------------------------------------------
#	Procedure: do_save
#	Purpose: save a SD graph into a file
#-------------------------------------------------------
proc do_save {} {
  global appFileName obj

  if {[file exists $appFileName]} {
    catch "mv $appFileName $appFileName~"
  }
  puts "FileName saving: $appFileName"
  if {[catch "open $appFileName w" outFile]} {
    AlertBox "$outFile"
  } else {
    # put node objects first 
    foreach i [array names obj] {
      set otype [lindex $obj($i) 1]
      if {$otype != 6 && $otype != 7} {
        puts $outFile "$obj($i)\n"
      } 
    }
    # put link objects 
    foreach i [array names obj] {
      set otype [lindex $obj($i) 1]
      if {$otype == 6 || $otype == 7} {
        puts $outFile "$obj($i)\n"
      } 
    }
    close $outFile
  }
}

#-------------------------------------------------------
#	Procedure: do_save
#	Purpose: save a SD graph into a specific file name
#-------------------------------------------------------
proc do_save_as {} {
  global appFileName 
  
  set selFile [file_window "Save File As"]
  if {"$selFile" != ""} {
    set appFileName $selFile
    do_save
    show_file_name
  }
}

#-------------------------------------------------------
#	Procedure: do_delete
#	Purpose: delete a SD graph file from the directory
#-------------------------------------------------------
proc do_delete {} {

  set selFile [file_window "Delete File"]
  if {"$selFile" != ""} {
    if {[catch "exec rm $selFile" delResult]} {
      puts stderr "$delResult"
    } else {
      puts "File $selFile has been deleted"
      set filename $selFile
      set filename [append filename {.equ}]
      if {[catch "exec rm $filename" delResult]} {
        puts stderr "$delResult"
      } else {
        set filename $selFile
        set filename [append filename {.init}]
        if {[catch "exec rm $filename" delResult]} {
          puts stderr "$delResult"
	}
      }
    }
  }
}

#-------------------------------------------------------
#	Procedure: show_file_name
#	Purpose: show file name on the label widget
#-------------------------------------------------------
proc show_file_name {} {
  global appFileName 
  
  destroy .menu.fname .menu.position
  label .menu.position -text "X:0 Y:0" -relief raised
  label .menu.fname -text "File name: $appFileName" -relief raised
  pack .menu.fname .menu.position -side right
}

#-------------------------------------------------------
#	Procedure: delete_all
#	Purpose: delete all object on the canvas
#-------------------------------------------------------
proc delete_all {} {
  global obj
  set c .plate.right.board

  $c delete all
  unset_obj
}

#-------------------------------------------------------
#	Procedure: unset_obj
#	Purpose: release obj variable arrays
#-------------------------------------------------------
proc unset_obj {} {
  global obj obj_flg

  if {$obj_flg == 0} {
    return
  } else {
    foreach i [array names obj] {
      unset obj($i)
    }
  }
}
