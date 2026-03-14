<?php
require('mbfpdf.php');

// EUC-JP->SJIS ﾊﾑｴｹ､ｫﾆｰﾅｪ､ﾋｹﾔ､ﾊ､・ｻ､・・遉ﾋ mbfpdf.php ﾆ筅ﾎ $EUC2SJIS ､・// true ､ﾋｽ､ﾀｵ､ｹ､・ｫ｡｢､ｳ､ﾎ､隍ｦ､ﾋｼﾂｹﾔｻ､ﾋ true ､ﾋﾀﾟﾄ熙ｷ､ﾆ､簗ﾑｴｹ､ｷ､ﾆ､ｯ､ﾞ､ｹ｡｣
$GLOBALS['EUC2SJIS'] = true;

$pdf=new MBFPDF();
$pdf->AddMBFont(GOTHIC ,'SJIS');
$pdf->AddMBFont(PGOTHIC,'SJIS');
$pdf->AddMBFont(MINCHO ,'SJIS');
$pdf->AddMBFont(PMINCHO,'SJIS');
$pdf->AddMBFont(KOZMIN ,'SJIS');
$pdf->Open();
$pdf->AddPage();
$pdf->SetFont(GOTHIC,'U',20);
$pdf->Write(10,"MS･ｴ･ｷ･ﾃ･ｯ ﾀﾝｻ・18 C ｼｾﾅﾙ 83 %\n");
$pdf->SetFont(PGOTHIC,'U',20);
$pdf->Write(10,"MSP･ｴ･ｷ･ﾃ･ｯ ﾀﾝｻ・18 C ｼｾﾅﾙ 83 %\n");
$pdf->SetFont(MINCHO,'U',20);
$pdf->Write(10,"MSﾌﾀﾄｫ ﾀﾝｻ・18 C ｼｾﾅﾙ 83 %\n");
$pdf->SetFont(PMINCHO,'U',20);
$pdf->Write(10,"MSPﾌﾀﾄｫ ﾀﾝｻ・18 C ｼｾﾅﾙ 83 %\n");
$pdf->SetFont(KOZMIN,'U',20);
$pdf->Write(10,"ｾｮﾄﾍﾌﾀﾄｫ ﾀﾝｻ・18 C ｼｾﾅﾙ 83 %\n");
$pdf->Output();
?>
