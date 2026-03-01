#!/usr/bin/perl

;#-----------------------------------
;#
;#  Graphical Access Counter v3.2
;#  (c)rescue@ask.ne.jp
;#
;#-----------------------------------

# 設置構成
#
# ホームページディレクトリ
#            |
#            |-- index.html (このファイルにカウンタを表示する) (*)
#            |
#            |          このファイルのカウンタを表示させたい場所に次のSSIコマンドを書く.
#            |          <!--#exec cmd="./count/count.pl"-->
#            |
#            |---- count/ <777>
#            |       |
#            |       |-- count.pl (このスクリプト) <755>
#            |       |-- count.txt (カウント開始数が入ったファイル) <666>
#            |       |-- count.tmp (空のファイル) <666>
#            |
#            |---- images/
#                    |
#                    |-- 0.gif (数字画像 0)
#                    |-- 1.gif (数字画像 1)
#                    |-- 略
#                    |-- 9.gif (数字画像 9)

#■(*)印のファイルから見たcount/ディレクトリの位置を設定(パス) <絶対パスで書いてもよい>
$basedir = './count/';

#■(*)印のファイルから見たimages/ディレクトリの位置を設定(ＵＲＬ) <http://から書いてもよい>
$graphics = './image/';

#■ＣＧＩ二重起動防止ロック処理
#　通常は 1 に設定しますが、symlinkの使えない極一部のサーバでは「常にBUSY」になりますので、
#　その場合は 2 に設定してください.　1 よりも 2 の方が処理が甘くなります.
#
#  　0:ロック処理しない 1:ロック処理(symlink) 2:ロック処理(open)

$lock_key = 2;

#■cpコマンドのパス

$cp = 'cp';

#◇--- ここから先は十分な知識がない場合は改変しないこと ---◇

$file = $basedir . 'count.txt';
$temp = $basedir . 'count.tmp';
$lockfile = $basedir . 'count.lock';

if ($lock_key == 1) { &lock; }
elsif ($lock_key == 2) { &lock2; }

system("$cp $file $temp");

if (!open(IN,$temp)) { &error('ERROR2'); }
$count = <IN>;
close IN;

$count++;

if (!open(NEW,">$file")) { &error('ERROR2'); }
print NEW $count;
close NEW; 

foreach (0..length("$count")-1) { $img = substr($count,$_,1);
print "<img src=\"$graphics$img.gif\" alt=\"$img\" border=\"0\">"; }

if (-e $lockfile) { unlink($lockfile); }
exit;

sub lock {

	local($retry) = 3;
	while (!symlink(".", $lockfile)) {

		if (--$retry <= 0) { &error('BUSY'); }
		sleep(2);
	}
}

sub lock2 {

	$c = 0;
	while(-f "$lockfile") {

		$c++;
		if ($c >= 3) { &error('BUSY'); }
		sleep(2);
	}
	open(LOCK,">$lockfile");
	close(LOCK);
}

sub error {

	if (-e $lockfile) { unlink($lockfile); }
	print $_[0];
	exit;
}
