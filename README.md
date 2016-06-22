# Volleyball
organize volleyball tournaments up to 45 teams

###Version 0.9  
added game plan for 45 teams
added base class basegamehandling
added tables and view (vr & zw gri) to database

###Version 0.8
added ftp upload for db file
added read ftp config from ini file

###Version 0.7
split up program to gui and worker

###Version 0.6
rebuild ergebnisse widget
uses now editable sqltablemodel for tickets to solve internal and external double team results
rebuild spiele und ergebnisse widget, get result data via views
bugfix add kreuzspiel gametime to start time platzspiele

###Version 0.5
added game plan for 40 teams
bugfix for checkequalresults in vorrunde and zwischenrunde, handling for two or more equal teams
add button function to show platzierungen_view => show new window to show results
catch button click generate if round was already generated

###Version 0.4
-add: game plan for 35 teams,
-add: key events to itemdelegates, handle copy and paste, return esc keys, 
-add: icons to widgets

-fix: recalculate time event

          
###Version 0.3
*fixed commit bug for sqltablemodels => dont use removecolumn
*instead tableview => hidecolumn
*add widget to show results and game plan => use view_division_results in view_all_results,
*fixed tableview input and column numbers,
*fixed generate zwischenrunde_spielplan
*fixed insert fieldnumbers and fieldnames
*add time calculation for whole tournament

###Version 0.2
*remastered system
*removed web views
*use sqlite for datastorage

###Version 0.1
*implemented game plan system
*tournament setup (time, sets, ...)
*add calculations
*add web views
*add postgresql database
*add reports

##Copyright
Copyright(C) 2015 cfr
