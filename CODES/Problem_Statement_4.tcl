set ns  [new Simulator]

$ns color 0 magenta
$ns color 1 red
$ns color 2 green
$ns color 3 orange
$ns color 4 yellow
$ns color 5 blue
$ns color 6 black
$ns color 7 brown
$ns color 8 purple

#dynamic routing
$ns rtproto DV

# nam file for tracing the network
set nf [open Problem_Statement_4.nam w]
$ns namtrace-all $nf

#finish process to end the tcl program
proc finish {} {
        global ns nf
        $ns flush-trace
        close $nf
        exec nam Problem_Statement_4.nam
        exit 0
        }

#input n
puts "Enter N (number of nodes) : "
set N [gets stdin]

#creating Nodes        
for {set i 0} {$i<$N} {incr i} {
set n($i) [$ns node]
}

#Creating Links: SFQ = Stochastic Fair Queuing if queue gets full
for {set k -1; set i 0; set j 1} {$i<$N} {incr k; incr i; incr j} {
    if {$j == $N} {
        $ns duplex-link $n($i) $n(0) 512Kb 10ms SFQ
    } elseif {$i == 0} {
        $ns duplex-link $n(0) $n(1) 512Kb 10ms SFQ
        
    } else {
        $ns duplex-link $n($i) $n($j) 512Kb 10ms SFQ
    }
 
}

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

# #UDP_Config
# set udp0 [new Agent/UDP]
# $udp0 set class_ 2
# $ns attach-agent $n(2) $udp0

# set null0 [new Agent/Null]
# $ns attach-agent $n(5) $null0

# $ns connect $udp0 $null0

# #CBR Config
# set cbr0 [new Application/Traffic/CBR]
# $cbr0 set rate_ 256Kb
# $cbr0 attach-agent $udp0

#FTP Config
for {set i 0} {$i < $k} {incr i} {

        set ftp($i) [new Application/FTP]
        $ftp($i) attach-agent $tcp($i)
}



#Scheduling Events
# $ns rtmodel-at 0.5 down $n(0) $n(5)
# $ns rtmodel-at 0.9 up $n(0) $n(5)

# $ns rtmodel-at 0.7 down $n(0) $n(4)
# $ns rtmodel-at 1.2 up $n(0) $n(4)

for {set i 0} {$i < $k} {incr i} {

        $ns at 0.1 "$ftp($i) start"
        
        $ns at 1.5 "$ftp($i) stop"
        
}


$ns at 2 "finish"
$ns run
