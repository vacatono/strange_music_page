<?
//
//	writefpdf.inc
//	
//	PDF書き出しのFPDFバージョン
//


require_once("/var/common/class/fpdf153/mbpdf.php");

class writefpdf extends MBFPDF
{
	var $pdf;					// FPDF-Object
	var $filename = "";			// ファイル名
	var $font = "HeiseiMin-W3";	// 標準のフォント名
	var $fontsize = 3.8;		// 標準のフォントサイズ


//	コンストラクタのオーバーライド
function writefpdf($o="P",$u="mm",$f="A4"){
	$this->mbfpdf($o,$u,$f);
}



// Begin Page
function BeginPage($outname){
	$this->AddPage();
}

// ページ終了処理
function EndPage(){
	return true;
}

// ブラウザに出力
function OutputBuffer(){
	$this->Output();
}




function LineText($x,$y,$w,$text,$opt=array()){

	pdf_show_xy($this->pdf,mb_convert_encoding($text,"SJIS","EUC"),$px,$y);
}

// 画像配置
function SetImage($file,$x,$y,$filetype="jpeg"){
	$im = pdf_open_image_file($this->pdf,$filetype,$file);
	pdf_place_image($this->pdf,$im,$x,$y,1);
	pdf_close_image($this->pdf,$im);
}

//	画像配置 (倍率を自動的に取得)
function SetImageAuto($file,$x,$y,$w,$h){
	if(!$ppt = getimagesize($file)){
		return false;
	}
	if($ppt[2]==1){ $type = "gif";
	}elseif($ppt[2]==2){ $type = "jpeg";
	}elseif($ppt[2]==3){ $type = "png";
	}
	$im = pdf_open_image_file($this->pdf,$type,$file);
	
	if(($w/$h) > ($ppt[0]/$ppt[1])){	
		$mag = $h/$ppt[1];		//	height
	}else{
		$mag = $w/$ppt[0];		//	width
	}
	pdf_place_image($this->pdf,$im,$x,$y,$mag);
	pdf_close_image($this->pdf,$im);
}

function SetBox($x,$y,$w,$h,$bg_col="",$line_col="",$line_w=0){
	if(!$bg_col && (!$line_col && $line_w==0)){
		return;
	}

	// 塗り色と線の色の設定
	pdf_setcolor($this->pdf,"fill","rgb",(float)('0x'.substr($bg_col,1,2))/255,(float)('0x'.substr($bg_col,3,2))/255,(float)('0x'.substr($bg_col,5,2))/255);
	pdf_setcolor($this->pdf,"stroke","rgb",(float)('0x'.substr($line_col,1,2))/255,(float)('0x'.substr($line_col,3,2))/255,(float)('0x'.substr($line_col,5,2))/255);
	if($line_w>0){ pdf_setlinewidth($this->pdf,$line_w); }

	pdf_rect($this->pdf,$x,$y,$w,$h);

	if($bg_col && ($line_w>0) && $line_col){
		pdf_fill_stroke($this->pdf);		// 線と塗りの設定がある場合
	}elseif($bg_col){
		pdf_fill($this->pdf);				// 塗りの設定だけある場合
	}else{
		pdf_stroke($this->pdf);				// 線の設定だけ、もしくは線の設定無し。
	}
}

function SetImageBox($file="",$x,$y,$w,$h,$valign="",$align="",$bg_col="#ffffff",$line_col="#ffffff",$line_w=0,$padding=0){
	if(strlen($file)){	// 画像があったとき
		$size = getimagesize($file);
		if($size && $size[0]<=$w && $size[1]<=$h){		// 画像のチェック
			$fileok = 1;
		}

		if($fileok){
			if($size[2]=='1'){		// ファイルタイプのチェック
				$ftype = "gif";
			}elseif($size[2]=='2'){
				$ftype = "jpeg";
			}elseif($size[2]=='3'){
				$ftype = "png";
			}else{
				return false;
			}
			// x座標
			if($align=="center"){
				$px = $x + ($w - $size[0])/2;
			}elseif($align=="right"){
				$px = $x + $w - $size[0] - $padding;
			}else{
				$px = $x + $padding;
			}
		
			// y座標
			if($valign=="middle"){
				$py = $y + ($h - $size[1])/2;
			}elseif($valign=="top"){
				$py = $y + $h - $size[1] - $padding;
			}else{
				$py = $y + $padding;
			}
		}
	}
	$this->SetBox($x,$y,$w,$h,$bg_col,$line_col,$line_w);

	if(strlen($file) && $fileok){
		$this->SetImage($file,$px,$py,$ftype);
	}
}

function SetImage2($file,$x,$y,$w,$h,$fit="auto",$align="left",$valign="bottom"){

	//	$fit: auto(横縦自動)/exp(伸張)/width(横)/height(縦)/nofit
	//	$align: left/center/right
	//	$valign: top/middle/bottom

	//	ファイルの存在確認
	if(!is_file($file)){ return false; }

	$size = getimagesize($file);
	if($size[2]==1){
		$im = imagecreatefromgif($file);
	}elseif($size[2]==2){
		$im = imagecreatefromjpeg($file);
	}elseif($size[2]==3){
		$im = imagecreatefrompng($file);
	}
	//	ファイル開けない場合false
	if(!$im){ return false; }

	if($fit=="auto"){
		if(($w/$h) > ($size[0]/$size[1])){	
			$fit = "height";
		}else{
			$fit = "width";
		}
	}


	if($fit=="exp"){
		//	強制リサイズ
		$im2 = imagecreatetruecolor($w,$h);
		imagecopyresampled($im2,$im,0,0,0,0,$w,$h,$size[0],$size[1]);
	}elseif($fit=="width"){
		$h2 = $size[1] * $w / $size[0];

		$im2 = imagecreatetruecolor($w,$h2);
		imagecopyresampled($im2,$im,0,0,0,0,$w,$h2,$size[0],$size[1]);

		if($valign=="middle"){
			$y = $y + ($h - $h2)/2;
		}elseif($valign=="top"){
			$y = $y + $h - $h2;
		}
	}elseif($fit=="height"){
		$w2 = $size[0] * $h / $size[1];

		$im2 = imagecreatetruecolor($w2,$h);
		imagecopyresampled($im2,$im,0,0,0,0,$w2,$h,$size[0],$size[1]);

		if($align=="center"){
			$x = $x + ($w - $w2)/2;
		}elseif($align=="right"){
			$x = $x + $w - $w2;
		}
	}else{
		$im2 = $im;
	}

	$tmpimg = "/tmp/".time();

	imagejpeg($im2,$tmpimg);
	imagedestroy($im);
	
	$this->SetImage($tmpimg,$x,$y);
	unlink($tmpimg);
	
}


}	// end of class [WritePdf]
?>
