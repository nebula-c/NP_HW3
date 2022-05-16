#!/usr/bin/perl -w

use Cwd;

$package = "pp13TeV_v2";
$maindir = getcwd();

$try = 102;

$jobname = sprintf("hist_${package}_try%03d",${try});

# open(FILE,"<file.lst");
open(FILE,"<list_allfile.lst");
@filelist = <FILE>;
close(FILE);

$nfiles = @filelist;
$nfiles_per_job = 8; #pp13TeV pythia (string shoving), 3500 files

$njobs = int($nfiles/$nfiles_per_job)+1;

print "$nfiles $nfiles_per_job $njobs\n";

$rundir = sprintf("${maindir}/runhist_${package}_try%03d",${try});
mkdir $rundir;

for ($irun=0; $irun<$njobs; $irun++){

	$wrkdir = "${rundir}/wrk_${irun}";
	mkdir $wrkdir;
	chdir $wrkdir;

	# open(FILE,">list_allfile.lst");
	open(FILE,">file.lst");

	for ($ii=0; $ii<$nfiles_per_job; $ii++){

		$ifile = $ii + $irun*$nfiles_per_job;
		if ( $ifile>=$nfiles ){
			last;
		}

		$filename = $filelist[$ifile];
		chomp($filename);

		if ($filename ){
			print FILE $filename."\n";
		}
	}#ii

	close(FILE);

	open(FILE, ">jobscript");
	print FILE "#!/bin/bash\n";

	print FILE "cp -av ${maindir}/NewRead.cpp .\n";
	print FILE "root -l -b -q 'NewRead.cpp+g($irun)'\n";
	$filename = sprintf("%s/outfile_%s_%05d.root",$rundir,$package,$irun);

	# print FILE "mv -v outfile_Read.root $filename\n\n";
	print FILE "rm -f *.pp\n\n";

	close(FILE);
	chmod 0755, "jobscript";

	chdir $wrkdir;
	open(FILE, ">condor");
	print FILE "Universe = vanilla\n";
	print FILE "Notification = Never\n";
	print FILE "Getenv = true\n";
	print FILE "Priority = +30\n";
	print FILE "Executable = jobscript\n";
	print FILE "JobBatchName = ${jobname}\n";
	print FILE "Log = jobscript.log\n";
	print FILE "Output = jobscript.out\n";
	print FILE "Error = jobscript.err\n";
	print FILE "Queue\n";
	close(FILE);

	system "condor_submit -append \"Accounting_Group=group_alice\" condor";

}
