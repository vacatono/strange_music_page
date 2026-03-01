#!/usr/bin/perl
# 検索スクリプト
# http://park.zero.ad.jp/vacatono/
# (c)vacatono@park.zero.ad.jp
# rev.0.02 2001.9.20
# this text written on EUC code!!

require './jcode.pl';
&jcode::convert(*search,'euc');	
open(KEYFILE,"$ARGV[0]") or die("cannot open $ARGV[0]");
while(<KEYFILE>){
	chomp;
	print "$_\n";
	if(/<h4>(.+?)<\/h4>/i){ $search = $1; }
	if(/<!-- liststart -->/){ last; }
}

print("<ul>\n");
@htmls = (`ls ../*.html`);
push(@htmls,'../../02liverepo.html');
push(@htmls,'../../01liverepo.html');
push(@htmls,'../../00liverepo.html');
push(@htmls,'../../99liverepo.html');
push(@htmls,'../../liverepo.html');

#### <a name= をキーワードにして、タイトル一覧。
foreach $html (@htmls){
	chomp $html;
	$title = "";

	open(FILE,"$html");
	while(<FILE>){
		&jcode::convert(*_,'euc');
		chomp();
		if(/<a name="(.+?)">(<h4>)*(.+?)<\/a>/i){
			$anchor = $1;
			$title = $3;
		}
		if(/<li>.*$search/i && $title){
			if(!grep(/$anchor/,@chk_anc)){
				print "<li><a href=\"$html#$anchor\">$title</a>\n";
				push(@chk_anc,$anchor);
			}
		}
	}
	close FILE;
}
close KEYFILE;
print << "END";
</ul>
<hr>
</body>
</html>
END
