#!/usr/bin/perl -w

$dim = $ARGV[0];
$IDcut = $ARGV[1];

@target = ("D","C","Fe","Pb");

$firstRun = 1;
$lastRun = 25;

for $k (0 .. $#target) {
  $logfile = "batch_plot_hists_$dim\_sig$IDcut\_$target[$k].log";
  $cmd = "batch_plot_hists.sh $target[$k] $firstRun $lastRun $dim $IDcut >& $logfile";
  print "$cmd\n\n";
#  system($cmd);
}
