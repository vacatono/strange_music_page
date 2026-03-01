#!/usr/bin/perl
# アンカー全部リスト作成スクリプト
# http://www1.vc-net.ne.jp/~keis
# (c)vacatono@livedoor.com
# 2001.10.2

require './jcode.pl';


@dirs = ('../music/*.html','../sympho/*.html','../smusic/*.html','../canterbury/*.html','../progre/*.html');

foreach $dir (@dirs){
	@files = (`ls $dir`);
	push @htmls, @files;
	}

#---分解/格納---
foreach $html (@htmls){
	chomp $html;

	open(FILE,"$html");
	@lines = <FILE>;
	close(FILE);

	$string = join(' ',@lines);
	$string =~ s/(\n|\r|\t)//g;
	$string =~ s/<a name\=\"/<!--taitoru--><a href\=\"$html\#/gi;
	&jcode::convert(*string,'euc');

	@partrecords = split('<div class="box1">',"$string");
	shift @partrecords;
	push @records, @partrecords;
	}

#---タイトル抜き出し---
foreach $record (@records){
	if ($record =~ m/<!--taitoru-->.*?<\/a>/gi){
		push @finds, $&;
		}
	}
#---表示---
open (LIST, ">listall.html"); 
print LIST '<html lang="ja">';
print LIST "<head><title>strange music page * all index</title>\n";
print LIST '<link rel="stylesheet" type="text/css" href="../style1.css">';
print LIST '<base target="main">';
print LIST "</head>\n";
print LIST '<body bgcolor="#ffffff">';
print LIST "\n";
print LIST '<hr><div align="right">strange music page<br>* * * all index<hr>';
print LIST "\n";
print LIST '</div>';
print LIST "\n";

print LIST "<p>\n";
#	print LIST "dir = @htmls";
print LIST "<ul>\n";
foreach $find (@finds){
	print LIST '<li>';
#---jcode---
	&jcode::convert(*find,'sjis');
	print LIST "$find\n";
	}
print LIST "</ul></body></html>\n";
