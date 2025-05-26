# plot: draw each result on separate 2-D graph
#-------------------------------------------------------
#       Procedure: Plot
#       Purpose: draw individual result on 2D graph
#-------------------------------------------------------
proc Plot {data_list} {
    global w ttt xxx yyy
    puts $w
    catch {destroy $w}
    toplevel $w
    dpos_plot $w 

    wm title $w $ttt
    wm iconname $w "Plot"
    set c $w.c

    message $w.msg -font -Adobe-Times-Medium-R-Normal-*-180-* -width 800 \
	    -bd 2 -relief raised -text "This window displays the simulation result by 2-D graph."
    canvas $c -relief raised -width 800 -height 500
#    button $w.ok -text "OK" -command "destroy $w"
    pack $w.msg $w.c -side top -fill x
#    pack $w.ok -side bottom -pady 5

    set font -Adobe-helvetica-medium-r-*-180-*

    $c create line 100 450 700 450 -width 2
    $c create line 100 450 100 50 -width 2
    # $c create text 225 20 -text " " -font $font -fill brown
   
    set hname [lindex $data_list 0]
    set vname [lindex $data_list 1]
    set iteration [lindex $data_list 2]
    set hstart [lindex $data_list 3]
    set hstep [lindex $data_list 4]
    set num_item [lindex $data_list 5]

    for {set i 0} {$i <= [llength $data_list]} {incr i} {
        puts [lindex $data_list $i]
    }

    for {set i 6} {$i <= [llength $data_list]} {incr i $num_item} {
      for {set j 0} {$j < $num_item} {incr j} {
        puts -nonewline [lindex $data_list [expr $i+$j]]
      }
      puts ""
    }

    # print X-axis
    set incre [expr $hstep*$iteration/10] 
    for {set i 0} {$i <= 10} {incr i} {
	set x [expr {100 + ($i*60)}]
	$c create line $x 450 $x 445 -width 2
	$c create text $x 454 -text [expr $incre*$i+$hstart] -anchor n \
		-font $font
    }
    set x [expr {55 + ($i*60)}]
    $c create text $x 442 -text $hname -anchor w -font $font

    # print Y-axis
    for {set i 0} {$i <= 10} {incr i} {
	set y [expr {450 - ($i*40)}]
	$c create line 100 $y 105 $y -width 2
#	$c create text 96 $y -text [expr $i*50].0 -anchor e -font $font
    }
    $c create text 10 23 -text $vname -anchor w -font $font
   
    set num_pts [expr [llength $data_list]-6]
    for {set j 0} {$j < $num_item} {incr j} {
      set max 0 
      set min 0 
      for {set i 6} {$i < [llength $data_list]} {incr i $num_item} {
	if {$max < [lindex $data_list [expr $i+$j]]} {
          set max [lindex $data_list [expr $i+$j]]
        }
	if {$min > [lindex $data_list [expr $i+$j]]} {
          set min [lindex $data_list [expr $i+$j]]
        }
      }
      set diff [expr $max-$min]
      if {$max/10*10 == $max} {
        set last $max
      } else {
        set last [expr ($max/10+1)*10]
      }

      if {$min >= 0} {
        set incre [expr $last/10] 
      } else {
        set incre [expr $diff/10] 
      }

      # select format to print Y values
      set v_num [expr 10*$incre]
      if {abs($v_num) > 100} {
        set format 1
      } elseif {abs($v_num) < 1} {
        set format 3
      } else {
        set format 2
      }

      # print V numbers
      for {set i 0} {$i < 11} {incr i} {
	set y [expr {450 - ($i*40)}]
        if {$min >= 0} {
          set v_num [expr $i*$incre]
 	} else {
	  if {$i == 0} {
	    set v_num $min
	  } else {
            set v_num [expr $v_num+$incre]
	  }
	}
        if {$format == 1} {
          set v_num [expr round($v_num)]
        } elseif {$format == 3} {
          set v_num [expr round([expr $v_num*1000])/1000.0]
        } elseif {$format == 2} {
          set v_num [expr round([expr $v_num*100])/100.0]
	}
	$c create text 96 $y -text $v_num -anchor e -font $font
      }

      # plot points 
      for {set i 6} {$i < [llength $data_list]} {incr i $num_item} {
        set x1 [expr {100 + (600*($i-6)/$num_item/($iteration-1))}]
	set y1 [lindex $data_list [expr $i+$j]]
	if {$min <0} {
	  set y1 [expr $y1-$min]
          set y1 [expr {450 - (400*$y1)/$diff}]
	} else {
          set y1 [expr {450 - (400*$y1)/$last}]
	}
	if {$i != 6} {
	  $c create line $x1 $y1 $x2 $y2 -width 1
	  set font -Adobe-Times-Medium-R-Normal-*-80-*
	  switch -exact -- $j {
	    0 {
		if {$num_pts <= 50} {
		  $c create oval [expr $x2-4] [expr $y2-4] \
                     [expr $x2+4] [expr $y2+4] -width 1 -outline black \
                     -fill white ; 
                  $c create text [expr $x2+3] $y2 -text [expr $j+1] -anchor e \
                     -font $font 
		}
	      }
	    1 {$c create line [expr $x1-4] [expr $y1-4] \
                [expr $x1+4] [expr $y1+4] -width 2;
	       $c create line [expr $x1+4] [expr $y1-4] \
                [expr $x1-4] [expr $y1+4] -width 2}
	  }
	}
	switch -exact -- $j {
	  0 {
	      if {$num_pts <= 50} {
		$c create oval [expr $x1-4] [expr $y1-4] \
                   [expr $x1+4] [expr $y1+4] -width 1 -outline black \
                   -fill white ; 
                $c create text [expr $x1+3] $y1 -text [expr $j+1] -anchor e \
                   -font $font 
	      }
	    }
	  1 {$c create line [expr $x1-4] [expr $y1-4] \
                [expr $x1+4] [expr $y1+4] -width 2;
	     $c create line [expr $x1+4] [expr $y1-4] \
                [expr $x1-4] [expr $y1+4] -width 2}
	}
	set font -Adobe-helvetica-medium-r-*-180-*
	set x2 $x1
	set y2 $y1
      }
    }
}

#-------------------------------------------------------
#       Procedure: Plot_all
#       Purpose: draw all results on a 2D graph
#-------------------------------------------------------
proc Plot_all {} {
  global w ttt xxx yyy
  global result_data rid pre_obj order

  set x_vname 250
  set pre_obj 0
  set enter 0

    puts $w
    catch {destroy $w}
    toplevel $w
    dpos_plot $w 

    wm title $w $ttt
    wm iconname $w "Plot all"
    set c $w.c

    set num_items [array size result_data]
    set win_width [expr 800+($num_items-1)*50]
    set win_height [expr 530+($num_items-1)*40]
    message $w.msg -font -Adobe-Times-Medium-R-Normal-*-180-* -width 800 \
	    -bd 2 -relief raised \
	-text "This window displays all simulation results on a 2-D graph."
    canvas $c -relief raised -width $win_width -height $win_height
#    button $w.ok -text "QUIT" -command "destroy $w"
    pack $w.msg $w.c -side top -fill x
#    pack $w.ok -side bottom -pady 5

    set font -Adobe-helvetica-medium-r-*-180-*
    set idx_font -Adobe-Times-Medium-R-Normal-*-100-*

    $c create line 100 450 700 450 -width 2
    $c create line 100 450 100 50 -width 2
    $c create line 700 450 700 50 -width 2
  
    # set titles for X,Y axes 
    foreach i [array names result_data] {
      set hname [lindex $result_data($i) 0]
      set vname [lindex $result_data($i) 1]
      set iteration [lindex $result_data($i) 2]
      set hstart [lindex $result_data($i) 3]
      set hstep [lindex $result_data($i) 4]
      set num_item [lindex $result_data($i) 5]
      break;
    } 

    # print X-axis
    set incre [expr $hstep*$iteration/10] 
    for {set i 0} {$i <= 10} {incr i} {
	set x [expr {100 + ($i*60)}]
	$c create line $x 450 $x 445 -width 2
	$c create text $x 454 -text [expr $incre*$i+$hstart] -anchor n \
		-font $font
    }
    set x [expr {70 + ($i*60)}]
    $c create text 400 480 -text $hname -font $font

  # print Y-axis and plot graphs
  set first_flg 1
  set color {black red SlateBlue3 gold2 SeaGreen3 orchid1 orange3}
  set color_ct 0 
  set ct 1
  foreach i [array names result_data] {
    set vname [lindex $result_data($i) 1]
    set num_pts [expr [llength $$result_data($i)]-6]
    if {$first_flg == 1} {
      # print scale
      for {set j 0} {$j <= 10} {incr j} {
	set y [expr {450 - ($j*40)}]
	$c create line 100 $y 105 $y -width 2
	$c create line 700 $y 695 $y -width 2
      }
      # print Vname
      set x_pos 700
      set y_pos 500 
      set oid [$c create rectangle [expr $x_vname-20] [expr $y_pos-10] \
	[expr $x_vname+20] [expr $y_pos+10] -width 1 \
	-fill [lindex $color $color_ct]]
      $c create text [expr $x_vname+3] $y_pos -text [expr $color_ct+1] \
		-anchor e -font $idx_font -fill white
      $c addtag item_rect withtag $oid
      set order($ct) $i
      set ct [expr $ct+1]
      $c create text [expr $x_vname+50] $y_pos -text $vname -anchor w \
		-font $font
    } else {
      set x_pos [expr $x_pos+60]
      set y_pos [expr $y_pos+30]
      set oid [$c create rectangle [expr $x_vname-20] [expr $y_pos-10] \
	[expr $x_vname+20] [expr $y_pos+10] -width 1 \
	-fill [lindex $color $color_ct]]
#      $c create oval [expr $x_vname-4] [expr $y_pos-4] \
#              [expr $x_vname+4] [expr $y_pos+4] -width 1 -outline black \
#               -fill white ;
      $c create text [expr $x_vname+3] $y_pos -text [expr $color_ct+1] \
		-anchor e -font $idx_font -fill black
      $c addtag item_rect withtag $oid
      set order($ct) $i
      set ct [expr $ct+1]
      $c create text [expr $x_vname+50] $y_pos -text $vname -anchor w \
		-font $font
    }
    # find max range
    set max 0 
    set min 0
    for {set j 6} {$j < [llength $result_data($i)]} {incr j $num_item} {
	if {$max < [lindex $result_data($i) $j]} {
          set max [lindex $result_data($i) $j]
        }
        if {$min > [lindex $result_data($i) $j]} {
          set min [lindex $result_data($i) $j]
        }
    }
    set diff [expr $max-$min]
    if {$max/10*10 == $max} {
      set last $max
    } else {
      set last [expr ($max/10+1)*10]
    }
    if {$min >= 0} {
	puts "last= $last"
        set incre [expr $last/10]
    } else {
        set incre [expr $diff/10]
    }
#    set num_digits [expr round(log10($max))]

    # select format to print Y values
    set v_num [expr 10*$incre]
    if {abs($v_num) > 100} {
      set format 1
    } elseif {abs($v_num) < 1} {
      set format 3
    } else {
      set format 2
    }

    # print V numbers
    for {set j 0} {$j < 11} {incr j} {
	set y [expr {450 - ($j*40)}]
        if {$min >= 0} {
          set v_num [expr $j*$incre]
        } else {
	  if {$j == 0} {
            set v_num $min
          } else {
            set v_num [expr $v_num+$incre]
	  }
        }
	if {$format == 1} {
	  set v_num [expr round($v_num)]
	} elseif {$format == 3} {
	  set v_num [expr round([expr $v_num*1000])/1000.0]
	} else {
	  set v_num [expr round([expr $v_num*100])/100.0]
	}
        if {$first_flg == 1} {
	  $c create text 96 $y -text $v_num \
		 -anchor e -font $font
	} else {
	  $c create text $x_pos $y -text $v_num \
		 -anchor e -font $font -fill [lindex $color $color_ct]
	}
    }
    if {$first_flg == 1} {
      set first_flg 0
    }

    # plot points
    for {set j 6} {$j < [llength $result_data($i)]} {incr j $num_item} {
      set x1 [expr {100 + (600*($j-6)/$num_item/($iteration-1))}]
      set y1 [lindex $result_data($i) [expr $j]]
      if {$min <0} {
        set y1 [expr $y1-$min]
        set y1 [expr {450 - (400*$y1)/$diff}]
      } else {
        set y1 [expr {450 - (400*$y1)/$last}]
      }
      if {$j != 6} {
        $c create line $x1 $y1 $x2 $y2 -width 1 -fill [lindex $color $color_ct]
        set font -Adobe-Times-Medium-R-Normal-*-80-*
        if {$num_pts <= 50} {
          $c create oval [expr $x2-4] [expr $y2-4] \
              [expr $x2+4] [expr $y2+4] -width 1 -outline black \
               -fill white ;
          $c create text [expr $x2+3] $y2 -text [expr $color_ct+1] -anchor e \
               -font $font
        }
      }
      if {$num_pts <= 50} {
        $c create oval [expr $x1-4] [expr $y1-4] \
              [expr $x1+4] [expr $y1+4] -width 1 -outline black \
              -fill white ;
        $c create text [expr $x1+3] $y1 -text [expr $color_ct+1] -anchor e \
              -font $font
      }
      set font -Adobe-helvetica-medium-r-*-180-*
      set x2 $x1
      set y2 $y1
    }
    set color_ct [expr $color_ct+1]
    set x 1
    set y 1
#    $c bind item_rect <Any-Enter> "puts hello"
#    $c bind item_rect <Any-Enter> "move_circle $c $ct %x %y"
#    $c bind item_rect <Any-Leave> "$c delete mov_obj"
#    bind $c <1> "move_circle $c $enter"
  }  
}

proc move_circle {w num x y} {
  global result_data rid pre_obj order

  set x [$w canvasx $x]
  set y [$w canvasy $y]
  $w itemconfig current -fill Red
  puts "y= $y"
  set y_pos 500
  # enter and check which one is selected
  for {set i 1} {$i < $num} {incr i} {
    if {$y >= [expr $y_pos-10] && $y <= [expr $y_pos+10]} {
      puts "match"
      break;
    }
    set y_pos [expr $y_pos+ 30]
  }
  puts "item# $i"
  set cur_obj $order($i)

    set iteration [lindex $result_data($cur_obj) 2]
    set num_item [lindex $result_data($cur_obj) 5]
    # find last
    set max 0
    for {set j 6} {$j < [llength $result_data($cur_obj)]} {incr j $num_item} {
        if {$max < [lindex $result_data($cur_obj) $j]} {
          set max [lindex $result_data($cur_obj) $j]
        }
    }
    if {$max/10*10 == $max} {
      set last $max
    } else {
      set last [expr ($max/10+1)*10]
    }
   #loop starts
    for {set j 6} {$j < [llength $result_data($cur_obj)]} {incr j $num_item} {
      set x1 [expr {100 + (600*($j-6)/$num_item/($iteration-1))}]
      set y1 [expr {450-(400*[lindex $result_data($cur_obj) [expr $j]])/$last}]
      puts "x1=$x1 y1=$y1"
      if {$j != 6} {
	puts "dx= [expr $x1-$ox] dy= [expr $y1-$oy]"
        set oid [$w create oval [expr $x1-4] [expr $y1-4] \
                     [expr $x1+4] [expr $y1+4] -width 1 -outline black \
                     -fill red] 
#        $w move move_obj [expr $x1-$ox] [expr $y1-$oy]
      } else {
        set oid [$w create oval [expr $x1-4] [expr $y1-4] \
                     [expr $x1+4] [expr $y1+4] -width 1 -outline black \
                     -fill red] 
	$w addtag move_obj withtag $oid
        puts "$oid created"
      }
      set ox $x1
      set oy $y1
      #delay
      for {set k 0} {$k <= 1000} {incr k} {
      }
    }
  set pre_obj $cur_obj
  $w delete move_obj
}
