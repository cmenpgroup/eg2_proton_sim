#!/usr/bin/perl -w

@target = ("D","C","Fe","Pb");
@dim = ("1d","2d","3d");
@cuts =("1.0","1.5","2.0","2.5","3.0");

$firstRun = 1;
$lastRun = 25;

for $i (0 .. $#dim) {
  for $j (0 .. $#cuts) {
    for $k (0 .. $#target) {
      $logfile = "batch_plot_hists_$dim[$i]_sig$cuts[$j]_$target[$k].log";
      $cmd = "batch_plot_hists.sh $target[$k] $firstRun $lastRun $dim[$i] $cuts[$j] >& $logfile";
      print "$cmd\n\n";
      system($cmd);
    }
  }
}
