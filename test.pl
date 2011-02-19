#!/usr/bin/perl -w
use strict;
use confidence_interval;

for my $i (1, 10, 100, 1000, 10000, 100000) {
    printf "%f\n", confidence_interval::wilson_lower_bound(2*$i, 10*$i, 0.1);
}
