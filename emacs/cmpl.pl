#!/usr/local/bin/perl
# $Id: cmpl.pl,v 1.3 1999-08-16 11:10:09 obachman Exp $
###################################################################
#
# FILE:    cmpl.pl
# PURPOSE: generate completion strings for singular emacs mode
# AUTHOR: obachman
####
$Usage = <<EOT;
$0 [-Singular binary] [-hlp file] [cmpl 'hlp|cmd|lib'] [-help]
Generates completion strings for singular emacs mode and prints it to STDOUT
EOT
  
#
# default settings of command-line arguments
#
$Singular = "../Singular/Singular";
$hlp = "../doc/singular.hlp";
$cmpl = "cmd";

#
# parse command line options
#
while (@ARGV && $ARGV[0] =~ /^-/)
{
  $_ = shift(@ARGV);
  if (/^-S(ingular)?$/)  { $Singular = shift(@ARGV); next;}
  if (/^-h(lp)?$/)       { $hlp = shift(@ARGV); next;}
  if (/^-c(mpl)?$/)      { $cmpl = shift(@ARGV); next;}
  if (/^-h(elp)?$/)      { print $Usage; exit;}
  die "Unrecognized option: $_\n$Usage";
}

#
# get array of strings
#
if ($cmpl eq 'cmd')
{
  $strings = `$Singular -tq --exec='reservedName();\$'`;
  die "Error in execution of: $Singular -tq --exec='reservedName();\$': $!\n"
    if ($?);
  @strings = split(/\s+/, $strings);
}
elsif ($cmpl eq 'lib')
{
  @strings = split(/\s+/, <>);
}
elsif ($cmpl eq 'hlp')
{
  open(FH, "<$hlp") || die "Can not open file $hlp: $!\n";
  while (<FH>)
  {
    if (/Node: Index/)
    {
      while (<FH>)
      {
	last if /\* Menu:/;
      }
      <FH>;
      while (<FH>)
      {
	last if /^\s*$/;
	s/\* (.*):.*/$1/;
	s/(.*) <\d+>$/$1/;
	s/^\s*(.*)\s*/$1/;
	s/([\\#"])/\\$1/g; #'
	push @strings, $_ if $_ && $_ ne $prev;
	$prev = $_;
      }
      last;
    }
  }
  close(FH);
}
else
{
  die "Error: Can not make completion list for $cmpl\n $Usage";
}
print STDOUT <<EOT;
; Do not edit this file: It was automatically generated by $0
(setq singular-completion-$cmpl-alist
  '(
EOT
#' prevents breaking of fontification
 
foreach $string (@strings)
{
  print STDOUT qq[    ("$string")\n];
}

print STDOUT "))\n";

