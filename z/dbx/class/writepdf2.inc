<?
# pdfwriter.inc
# PDF書き出しクラス2、フォントロード対応
#

class writepdf2
{
	var $pdf;			// pdf stream
	var $height;		// page height
	var $width;			// page width
	var $fonts;			// font settings array
	var $filename;		// filename
	var $hyphe_head = array();	//	Japanese-Hyphenation
	var $hyphe_tail = array();	//	Japanese-Hyphenation
	var $def_font = "MS-PMincho";
	var $def_size = "6";
	var $scale  = 1;
	var $horiz = 100;
	var $pxmm = 2.835;		//	px - mm (72/25.4)

// コンストラクタ
// $this->pdfを指定ファイル名で開いて、SetSizeをコール
// licenceをセット
function writepdf2($filename="",$size="A4",$mmconv=0){
	if($filename){ $this->filename = $filename; };


	$this->pdf = pdf_new();
//	pdf_set_parameter($this->pdf,"license","L500202-010000-103727-0F944A");
	pdf_open_file($this->pdf,$this->filename);
	if($mmconv){
		$this->scale = $this->pxmm;
	}
	
	$this->SetSize($size);
	$this->iniLoadFont();
	$this->setHypheHead();
	$this->setHypheTail();
	pdf_set_parameter($this->pdf,"textformat","utf8");
}

//	行頭禁則処理文字列の定義
function setHypheHead($hyphe=""){
	if($hyphe){
		$this->hyphe_head = array_merge($this->hyphe_head,$hyph);
		array_unique($this->hyphe_head);
	}else{
		$this->hyphe_head = array('!','%',')',',','.',':',';','?',']','}','?','°','’','”','‰','′',
			'″','℃','、','。','々','〉','》','」','』','】','〕','゛','゜','ゝ','ゞ','・','ヽ','ヾ','！',
			'％','）','，','．','：','；','？','］','｝','｡','｣','､','･','ﾞ','ﾟ','>','＞','ー','-');
	}
}
//	行末禁則処理文字列の定義
function setHypheTail($hyphe=""){
	if($hyphe){
		$this->hyphe_tail = array_merge($this->hyphe_tail,$hyph);
		array_unique($this->hyphe_tail);
	}else{
		$this->hyphe_tail = array('$','(','[','‘','“','〈','《','「','『','【','〔','＄','（','［','｛','｢','£','￥','<','＜');
			
	}
}

//	フォントハンドルの初期設定（MS-P明朝 + MS-Pゴシック）
function iniLoadFont($app=array()){
	pdf_set_parameter($this->pdf,"FontOutline","ArialItalic=/usr/X11R6/lib/X11/fonts/windows/ARIALI.TTF");
	pdf_set_parameter($this->pdf,"FontOutline","ArialBold=/usr/X11R6/lib/X11/fonts/windows/ARIALBD.TTF");
	pdf_set_parameter($this->pdf,"FontOutline","PlatinoLinotypeItalic=/usr/X11R6/lib/X11/fonts/windows/palai.TTF");
	pdf_set_parameter($this->pdf,"FontOutline","MS-Gothic=/usr/X11R6/lib/X11/fonts/windows/MSGOTHIC.TTC");
	pdf_set_parameter($this->pdf,"FontOutline","MS-Mincho=/usr/X11R6/lib/X11/fonts/windows/MSMINCHO.TTC");
	pdf_set_parameter($this->pdf,"FontOutline","MS-PMincho=/usr/X11R6/lib/X11/fonts/windows/MSMINCHO.TTC");
	$this->fonts['ArialItalic'] = pdf_load_font($this->pdf,"ArialItalic","unicode","");
	$this->fonts['ArialBold'] = pdf_load_font($this->pdf,"ArialBold","unicode","");
	$this->fonts['PlatinoLinotypeItalic'] = pdf_load_font($this->pdf,"PlatinoLinotypeItalic","unicode","");
	$this->fonts['MS-Gothic'] = pdf_load_font($this->pdf,"MS-Gothic","unicode","");
	$this->fonts['MS-Mincho'] = pdf_load_font($this->pdf,"MS-Mincho","unicode","");
	$this->fonts['MS-PMincho'] = pdf_load_font($this->pdf,"MS-PMincho","unicode","");
	
	pdf_set_parameter($this->pdf,"FontOutline","MS-PGothic=/usr/X11R6/lib/X11/fonts/windows/MSGOTHIC.TTC");
	$this->fonts['MS-PGothic'] = pdf_load_font($this->pdf,"MS-PGothic","unicode","");
//	$this->fonts['MS-PGothic_glyph'] = pdf_load_font($this->pdf,"MS-PGothic","glyphid","");
//	$this->fonts['MS-PMincho_glyph'] = pdf_load_font($this->pdf,"MS-PMincho","glyphid","");
}

//	フォントファイルを定義して、フォント名を返す。
function LoadFont($fontname,$fontpath,$opt=""){
	$outline = pdf_set_parameter($this->pdf,"FontOutline",$fontname . "=" . $fontpath);
	$this->fonts[$fontname] = pdf_load_font($this->pdf,$fontname,"unicode","{$opt}");
	if($this->fonts[$fontname]){
		return $fontname;
	}else{
		return false;
	}
}


// Set Page Size (mm)
function SetSize($size="A4",$height="",$width=""){
	switch($size){
		case A4:
			$this->height = 297;
			$this->width = 210;
			break;
		case A4R:
			$this->height = 210;
			$this->width = 297;
			break;
		case A3:
			$this->height = 420;
			$this->width = 297;
			break;
		case B4:
			$this->height = 364;
			$this->width = 257;
			break;
		case postcard:
			$this->height = 154;
			$this->width = 107;
			break;
		default:
			if($height && $width){
				$this->height = $height;
				$this->width = $width ;
			}else{
				$this->height = 297;
				$this->width = 210;
			}
			break;
	}
}



function EndPdf(){
	if(pdf_get_parameter($this->pdf,"scope")=="page"){
		pdf_end_page($this->pdf);
	}
	pdf_close($this->pdf);
}

// PDIで既存のPDFを読み込み
function LoadPDI($filename){
	// open PDF
	$doc = PDF_open_pdi($this->pdf,$filename,"",0);
	// open first page
	$page = PDF_open_pdi_page($this->pdf,$doc,1,"");
	PDF_fit_pdi_page($this->pdf,$page,0,0,"adjustpage");

	//	スケール合わせもう一回
	pdf_scale($this->pdf,$this->scale,$this->scale);
	$this->width = pdf_get_value($this->pdf,"pagewidth") * $this->scale;
	$this->height = pdf_get_value($this->pdf,"pageheight") * $this->scale;
}

function setPDI($filename,$x,$y){
	$doc = pdf_open_pdi($this->pdf,$filename,"",0);
	$page = pdf_open_pdi_page($this->pdf,$doc,1,"") or die("cannot open pdi -page");
	$sc = 1/$this->scale;
	pdf_place_pdi_page($this->pdf,$page,$x,$y,$sc,$sc);
	pdf_close_pdi_page($this->pdf,$page);
	pdf_close_pdi($this->pdf,$doc);
	

}



// Begin Page ( including 'px' -> 'mm' )
function BeginPage($outname){
	if(pdf_get_parameter($this->pdf,"scope")=="page"){
		pdf_end_page($this->pdf);
	}
	pdf_begin_page($this->pdf,$this->width*$this->scale,$this->height*$this->scale);
	pdf_scale($this->pdf,$this->scale,$this->scale);
	pdf_add_bookmark($this->pdf,$outname);
}

// End Page
function EndPage(){
	if(pdf_get_parameter($this->pdf,"scope")=="document"){
		pdf_end_page($this->pdf);
	}
}

// ブラウザに出力
function OutputBuffer(){
	$buffer = PDF_get_buffer($this->pdf);
	header("Content-Type: application/pdf");
	header("Content-Length: " . strlen($buffer));
	header("Content-Disposition: inline; filename=pdi.pdf");
	print($buffer);
	PDF_delete($this->pdf);
}

// 文字列の長さを測る 
function TextSize($text,$fontname,$fontsize){
	if(!$this->fonts[$fontname]){
		//print("no define fontname<br>");
		return false;
	}
	$text = mb_convert_encoding($text,"UTF-8");
	$size = pdf_stringwidth($this->pdf,$text,$this->fonts[$fontname],$fontsize);
	return $size;
}



// 指定したサイズに合わせて文字列を分割する。UTF-8で計るけど返すのはEUC
function SplitText($width,$text,$fontname="",$fontsize="",$indent=""){

	//	初期設定
	if(!$fontname){ $fontname = $this->def_font; }
	if(!$fontsize){ $fontname = $this->def_size; }

	if(!$this->fonts[$fontname]){
		//print("not define {$fontname}<br>");
		return false;
	}
	//	改行コードを\nに統一
	$text = eregi_replace("\r\n|\r","\n",$text);

	pdf_setfont($this->pdf,$this->fonts[$fontname],$fontsize);

	$row = 0;
	$indentflag = 0;

	for($i=0;$i<mb_strlen($text);$i++){
		$char = mb_substr($text,$i,1);
		$len += pdf_stringwidth($this->pdf,mb_convert_encoding($char,"UTF-8"),$this->fonts[$fontname],$fontsize);

		if(mb_eregi("[a-z,0-9,>\.,\,]",$char)){
			$contents[$row] .= mb_substr($text,$i,1);
			continue;
		}


		if($char=="\n"){
			//	改行コード、強制改行
			$contents[$row] .=  "";
			$row ++ ;
			$len = 0;
		}elseif($len>$width){

			//	この時の行末文字
			$tailchar = mb_substr($contents[$row],-1,1);

			//	改行して、この文字を頭に。
			if(in_array($char,$this->hyphe_head)){
				//print('行頭禁則' . htmlspecialchars($char));

				//	行頭禁則
				$contents[$row] .=  $char;
				//	禁則二重処理
				if(in_array(mb_substr($text,$i+1,1),$this->hyphe_head)){
					//print('二重行頭禁則' . htmlspecialchars($char));
					$contents[$row] .= mb_substr($text,$i+1,1);
					$i++;
				}
				$row++;
				$contents[$row] .=  $indent;

				$len = pdf_stringwidth($this->pdf,mb_convert_encoding($contents[$row],"UTF-8"),$this->fonts[$fontname],$fontsize);
			}elseif(in_array($tailchar,$this->hyphe_tail)){
				//print('行末禁則' . htmlspecialchars($tailchar));

				//	行末禁則
				$contents[$row] = mb_substr($contents[$row],0,-1);
				$row++;
				$contents[$row] .= $indent . $tailchar;
				$len = pdf_stringwidth($this->pdf,mb_convert_encoding($contents[$row],"UTF-8"),$this->fonts[$fontname],$fontsize);
				$contents[$row] .= $char;
				$len += pdf_stringwidth($this->pdf,mb_convert_encoding($char,"UTF-8"),$this->fonts[$fontname],$fontsize);
			}else{
				//	通常改行
				if(strlen(mb_substr($text,$i+1)) > 2){
					$row++;
					$len = 0;
					$contents[$row] .= $indent . $char;
					$len += pdf_stringwidth($this->pdf,mb_convert_encoding($contents[$row],"UTF-8"),$this->fonts[$fontname],$fontsize);
				}else{
					//	残り1文字以下ならくっつけちゃう
					//print("Jointing"  . $i . " " .  $contents[$row] . "+" .  mb_substr($text,$i) . "<Br>");
					$contents[$row] .= mb_substr($text,$i);
					break;

				}
			}
		}else{
			$contents[$row] .= mb_substr($text,$i,1);
		}
	}
	return $contents;
}

// テキスト書き出し
function TextBox($x,$y,$w,$h,$text,$fontname="",$fontsize="",$options=array()){

	if(!strlen($text)){ return false; }

	if(!$fontname){ $fontname = $this->def_font; }
	if(!$fontsize){ $fontsize = $this->def_size; }


	//	$optionsの処理
	//	$options['linepitch'] 	改行幅
	//	$options['valign'] 		縦位置
	//	$options['align'] 		横位置
	//	$options['chsp']		文字間
	//	$options['direction']	縦書き？
	//	$options['debug']		デバッグ

	if($options['chsp']){
		pdf_set_value($this->pdf,"charspacing",$options['chsp']);
	}

	if($options['debug']){
		pdf_setlinewidth($this->pdf,0.1);
		pdf_setcolor($this->pdf,"stroke","rgb",0,1,0);
		pdf_rect($this->pdf,$x,$y,$w,$h);
		pdf_stroke($this->pdf);
		pdf_setcolor($this->pdf,"stroke","rgb",0,0,0);
	}


	//	localize font handle
	pdf_setfont($this->pdf,$this->fonts[$fontname],$fontsize);
	$font = $this->fonts[$fontname];

	if($options['align']=="justify2" || $options['align']=="justify3L"){
		$textArr = array($text);
	}else{
		$textArr = $this->SplitText($w,$text,$fontname,$fontsize);
	}
	$rows = count($textArr);

	//	y座標の初期値の設定
	if($options['valign']=="middle"){
		$cy = $y + $h / 2 + ($fontsize + $options[linepitch]) * $rows / 2 - $fontsize;
	}elseif($options['valign']=="bottom"){
		$cy = $y + ($fontsize + $options[linepitch]) * $rows - $fontsize;
	}else{
		$cy = $y + $h - $fontsize;
	}

	foreach($textArr as $line){
		if($options['align']=="right"){
			$cx = $x + $w - pdf_stringwidth($this->pdf,mb_convert_encoding($line,"UTF-8"),$font,$fontsize);
		}elseif($options['align']=="center"){
			$cx = $x + $w/2 - pdf_stringwidth($this->pdf,mb_convert_encoding($line,"UTF-8"),$font,$fontsize)/2;
		}elseif($options['align']=="justify"){
			$chsp = ($w - pdf_stringwidth($this->pdf,mb_convert_encoding($line,"UTF-8"),$font,$fontsize))/mb_strlen($line);
			pdf_set_value($this->pdf,"charspacing",$chsp);
			$cx = $x;
		}elseif($options['align']=="justify2"){
			$jhoriz = $w/pdf_stringwidth($this->pdf,mb_convert_encoding($line,"UTF-8"),$font,$fontsize) * 100;
			pdf_set_value($this->pdf,"horizscaling",$jhoriz);
			$cx = $x;
		}elseif($options['align']=="justify3L"){
			$sw = pdf_stringwidth($this->pdf,mb_convert_encoding($line,"UTF-8"),$font,$fontsize);
			if($sw >= $w){
				$jhoriz = $w/pdf_stringwidth($this->pdf,mb_convert_encoding($line,"UTF-8"),$font,$fontsize) * 100;
				pdf_set_value($this->pdf,"horizscaling",$jhoriz);
			}
			$cx = $x;
		}else{
			$cx = $x;
		}
		if($options['direction']=='V'){
			if($line=='ー'){
				//	擬似 縦書き対応
				pdf_setfont($this->pdf,$this->fonts[$fontname . '_glyph'],$fontsize);
				pdf_set_parameter($this->pdf,"textformat","utf16");
				pdf_show_xy($this->pdf,chr(45).chr(69),$cx,$cy);
				pdf_setfont($this->pdf,$this->fonts[$fontname],$fontsize);
				pdf_set_parameter($this->pdf,"textformat","utf8");
			}else{
				pdf_show_xy($this->pdf,mb_convert_encoding($line,"UTF-8"),$cx,$cy);
			}
		}else{
			pdf_show_xy($this->pdf,mb_convert_encoding($line,"UTF-8"),$cx,$cy);
		}
		$cy -= $fontsize + $options['linepitch'];

	}
	pdf_set_value($this->pdf,"charspacing",0);
	pdf_set_value($this->pdf,"horizscaling",$this->horiz);
	return array($cx,$cy);
}


// 角の丸い矩形
function SMS_RECT($X,$Y,$W,$H,$R){
	// 下/左/上/右
	pdf_moveto($this->pdf,$X+$R,$Y);
	pdf_lineto($this->pdf,$X+$W-$R,$Y);
	pdf_stroke($this->pdf);
	pdf_moveto($this->pdf,$X,$Y+$R);
	pdf_lineto($this->pdf,$X,$Y+$H-$R);
	pdf_stroke($this->pdf);
	pdf_moveto($this->pdf,$X+$R,$Y+$H);
	pdf_lineto($this->pdf,$X+$W-$R,$Y+$H);
	pdf_stroke($this->pdf);
	pdf_moveto($this->pdf,$X+$W,$Y+$R);
	pdf_lineto($this->pdf,$X+$W,$Y+$H-$R);
	pdf_stroke($this->pdf);
	
	// 左下/右下/左上/右上
	pdf_arc($this->pdf,$X+$R,$Y+$R,$R,180,270);
	pdf_stroke($this->pdf);
	pdf_arc($this->pdf,$X+$W-$R,$Y+$R,$R,270,360);
	pdf_stroke($this->pdf);
	pdf_arc($this->pdf,$X+$R,$Y+$H-$R,$R,90,180);
	pdf_stroke($this->pdf);
	pdf_arc($this->pdf,$X+$W-$R,$Y+$H-$R,$R,0,90);
	pdf_stroke($this->pdf);
}
// おしまい


// 画像配置
function SetImage($file,$x,$y,$filetype="jpeg"){
	$im = pdf_open_image_file($this->pdf,$filetype,$file);
	pdf_place_image($this->pdf,$im,$x,$y,1);
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
}


?>
