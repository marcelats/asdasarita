#-------------------------------------------------------
#       Procedure: show_result
#       Purpose: the selections of displaying execution results
#-------------------------------------------------------
proc show_result {} {

  global result_data xxx yyy all_flg each_flg
  set xxx 650
  set yyy 0
  set all_flg 0
  set each_flg 0

  catch {destroy .buttons}
  toplevel .buttons 
  dpos .buttons
  wm title .buttons "Simulation Results"

  set xxx 150
  set yyy 150

  button .buttons.show -text " Show individual result " -command {show_each; \
	set each_flg 1}
  button .buttons.showall -text " Show all " -command {set ttt "Show All"; \
	set w ".plotall"; set all_flg 1; Plot_all}
  button .buttons.quit -text " Quit " -command "destroy_display"
  pack .buttons.quit .buttons.showall .buttons.show -side right
#  .buttons.showall config -bg PaleVioletRed4
  read_result 

  tkwait visibility .buttons 
  grab .buttons 
  tkwait window .buttons 
}

#-------------------------------------------------------
#       Procedure: destroy_display
#       Purpose: destroy all 2D graphs
#-------------------------------------------------------
proc destroy_display {} {
  global all_flg each_flg result_data

  destroy .buttons
  if {$all_flg == 1} {
    destroy .plotall
  }
  if {$each_flg == 1} {
   foreach i [array names result_data] {
    destroy .plot$i
   }
  }
}

#-------------------------------------------------------
#       Procedure: show_each
#       Purpose: show all individual results
#-------------------------------------------------------
proc show_each {} {
  global result_data w ttt

  foreach i [array names result_data] {
    set w ".plot$i"
    set ttt [lindex $result_data($i) 1]
    Plot $result_data($i)
  }
}

#-------------------------------------------------------
#       Procedure: read_result
#       Purpose: read execution results from files
#-------------------------------------------------------
proc read_result {} {
  global result_data

  #reset result_data
  if {[catch "unset result_data"]} {
    puts "result_data has been reset"
  }

  # read result data from file
  set fileName "Simul.Result"
  set firstRead 0
  if {[catch "open $fileName r" inFile]} {
    if {!$firstRead} {
      AlertBox "$inFile"
    }
  } else {
    set fileContents [read $inFile]
    close $inFile
    set display_num [lindex $fileContents 0]
    puts "num_items= $display_num"
  }

  for {set i 1} {$i <= $display_num} {incr i} {
    if {[catch "open $fileName$i r" inFile]} {
      if {!$firstRead} {
        AlertBox "$inFile"
      }
    } else {
      set result_data($i) [read $inFile]
      close $inFile
    }
  }
}

#-------------------------------------------------------
#       Procedure: dpos_plot
#       Purpose: decide the 2D window positions
#-------------------------------------------------------
proc dpos_plot w {
  global xxx yyy

  if {$w == ".plotall"} {
    wm geometry $w +100+100
  } else {
    wm geometry $w +$xxx+$yyy;
    set xxx [expr $xxx+20];
    set yyy [expr $yyy+20];
  }
}

#-------------------------------------------------------
#       Procedure: dpos
#       Purpose: decide the selection window position
#-------------------------------------------------------
proc dpos w {
  global xxx yyy

  wm geometry $w +$xxx+$yyy;
}
