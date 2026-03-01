#!/usr/bin/perl
# 検索スクリプト
# http://park.zero.ad.jp/vacatono/
# (c)vacatono@park.zero.ad.jp
# rev.0.02 2001.9.20
# this text written on EUC code!!

require './jcode.pl';
&jcode::convert(*search,'euc');	

@htmls = (`ls ../music/*.html`);
push(@htmls,'../02liverepo.html');
push(@htmls,'../01liverepo.html');
push(@htmls,'../00liverepo.html');
push(@htmls,'../99liverepo.html');
push(@htmls,'../liverepo.html');

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
		if(/<li>.*$search_arr{$key}/i && $title){
			print("$key $html $anchor $title\n");
		}
	}
	close(FILE);
}
