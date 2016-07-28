# Volleyball
organize volleyball tournaments up to 45 teams, Copyright(C) 2010 - 2016, cfr

###Version 10
add/change
- make stringlists (table column names) static 

fix
- classement window crash, no instance at beginning
- time calculation for tournament end, wrong tables selected for getmaxtime...

###Version 9  
add/change
- game plan for 45 teams
- base class basegamehandling for all rounds (qualifying, interim, crossgames, classement)
- tables and view (vr & zw gri) to database

###Version 8
add/change
- ftp upload for db file
- read ftp config from ini file

###Version 7
add/change
- split up program to gui and worker

###Version 6
add/change
- rebuild ergebnisse widget
- uses now editable sqltablemodel for tickets to solve internal and external double team results
- rebuild spiele und ergebnisse widget, get result data via views

fix
- kreuzspiel gametime to start time platzspiele

###Version 5
add/change
- game plan for 40 teams
- button function to show platzierungen_view => show new window to show results

fix
- checkequalresults in vorrunde and zwischenrunde, handling for two or more equal teams
- catch button click generate if round was already generated

###Version 4
add/change
- game plan for 35 teams,
- key events to itemdelegates, handle copy and paste, return esc keys
- icons to widgets

fix
- recalculate time event

###Version 3
add/change
- widget to show results and game plan => use view_division_results in view_all_results
- add time calculation for whole tournament

fix
- commit bug for sqltablemodels => dont use removecolumn instead tableview => hidecolumn
- fixed tableview input and column numbers
- fixed generate zwischenrunde_spielplan
- fixed insert fieldnumbers and fieldnames

###Version 2
add/change
- remastered system
- removed web views
- use sqlite instead of postgres for datastorage

###Version 1
add/change
- implemented game plan system
- tournament setup (time, sets, ...)
- calculations
- web views
- postgresql database
- reports
