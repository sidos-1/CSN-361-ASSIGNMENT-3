set ns  [new Simulator]
LanRouter set debug 0
$ns color 0 red
$ns color 1 yellow
$ns color 2 green
$ns color 3 orange
$ns color 4 magenta
$ns color 5 blue
$ns color 6 black
$ns color 7 brown
$ns color 8 purple

#dynamic routing
# $ns rtproto DV

# nam file for tracing the network
set nf [open Problem_Statement_5.nam w]
$ns namtrace-all $nf

#finish process to end the tcl program
proc finish {} {
        global ns nf
        $ns flush-trace
        close $nf
        exec nam Problem_Statement_5.nam
        exit 0
        }

#input n
puts "Enter N (number of nodes) : "
set N [gets stdin]

#creating Nodes
set lan_nodes ""
for {set i 0} {$i<$N} {incr i} {
set n($i) [$ns node]
append lan_nodes "$n($i) "
}

#Creating Links
    set lan_connection [$ns newLan $lan_nodes 0.2Mb 50ms LL Queue/SFQ MAC/Csma/Cd Channel]


#input k(number of pairs to be connected) pairs
puts "Enter k (number of pairs) : "
set k [gets stdin]
puts "Enter k pairs : "
set j 1
for {set i 0} {$i<$k} {incr i} {
        
        puts "Pair : $j \t Node 1 : "
        set n1($i) [gets stdin]
        puts "Pair : $j \t Node 2 : "
        set n2($i) [gets stdin]
        incr j
        
}



#TCP_Config
for {set i 0} {$i < $k} {incr i} {

        set tcp($i) [new Agent/TCP]
        $tcp($i) set class_ $i
        $ns attach-agent $n($n1($i)) $tcp($i)

        set sink($i) [new Agent/TCPSink]
        $ns attach-agent $n($n2($i)) $sink($i)

        $ns connect $tcp($i) $sink($i)
}


#FTP Config
for {set i 0} {$i < $k} {incr i} {

        set ftp($i) [new Application/FTP]
        $ftp($i) attach-agent $tcp($i)
}


for {set i 0} {$i < $k} {incr i} {

        $ns at 0.1 "$ftp($i) start"
        
        $ns at 1.5 "$ftp($i) stop"
        
}


$ns at 2 "finish"
$ns run
