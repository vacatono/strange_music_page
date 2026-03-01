<?
# File  :  checkform.inc
# Date  :  2003-06-09(月) 14:37:04
# Maker :  Kousuke Akiho
# Last Modify : Kousuke Akiho / 2003-06-09(月) 14:37:04 ---> New File ...


class CheckForm
{
	
	////	空白かどうかのチェック		//////////////////////////////////////////////////
	//
	//
	function Emp(&$Value){
		
		$Value = trim($Value);
		
		if(@!$Value){
			return 1;
		}
	}
	
	###	**** 空かどうかチェック2 ***
	function emp2(&$v){
		if(!$val=trim($v)){
			return 'を入力して下さい。';
		}
	}
	//
	//
	//////////////////////////////////////////////////////////////////////////////////////
	

	function Gaiji(&$Value){
		if(mb_ereg("[".chr(0xAD).chr(0xA1)."-".chr(0xAD).chr(0xFE).",".chr(0x8E).chr(0xA1)."-".chr(0x8E).chr(0xDF)."]",$Value,$regs)){
			return $regs[0];
		}else{
			return 0;
		}
	}

	function SjisGaiji(&$Value){
		mb_regex_encoding("SJIS");
		if(mb_ereg("[".chr(0x87).chr(0x40)."-".chr(0x87).chr(0x9E)."|".chr(0xED).chr(0x40)."-".chr(0xEE).chr(0xFC)."|".chr(0xFA).chr(0x40)."-".chr(0xFC).chr(0x4B)."]",$Value,$regs)){
			$gaiji = 1;
			//echo "<pre>";print_r($regs);echo "</pre>";
		}else{
			$gaiji = 0;
		}
		mb_regex_encoding("EUC-JP");
		return $gaiji;
	}
	

	
	////	半角チェック		//////////////////////////////////////////////////////////
	//
	//
	function Hankaku (&$Value){
		
		if($Value){
			$Value = mb_convert_kana($Value,"KVa");
		}else{
			return false;
		}
		
		if(ereg("[^-,0-9,A-Z,a-z,_,\(,\),\ ,!,?,*,+,\",#,\$,%,&,\^,\~,\\,\|,\>,\<,=,\`,\.,\:,\/]",$Value)){
			return 1;
		}else{
			return 0;
		}
		
	}
	function Hankaku2 (&$Value){
		if($Value){ $Value = mb_convert_kana($Value,"KVa");
		}else{ return false;
		}
		
		if(ereg("[^-,0-9,A-Z,a-z,_,\(,\),\ ,!,?,*,+,\",#,\$,%,&,\^,\~,\\,\|,\>,\<,=,\`,\.,\:,\/]",$Value)){
			return "を半角英数字で入力して下さい。";
		}else{
			return 0;
		}
	}
	//
	//
	/////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
			
	////	メールアドレスチェック		//////////////////////////////////////////////////
	//
	//
	function Mail(&$Value){
		if($Value){
			$Value = mb_convert_kana($Value,"KVa");
		}else{
			return 3;
		}
		
		if(eregi('^[-!#$%&\'*+\\.0-9=?A-Z^_`{|}~]+' . '@' . '[-!#$%&\'*+\\0-9=?A-Z^_`{|}~]+\.' . '[-!#$%&\'*+\\.0-9=?A-Z^_`{|}~]+$',$Value)){
			return 0;
		}elseif(!ereg("@",$Value)){
			return 1;
		}else{
			return 2;
		}
	}
	function mailchk(&$v){
		if($v){
			$v = mb_convert_kana($v,"KVa");
		}else{
			return 0;
		}
		
		if(!eregi('^[-!#$%&\'*+\\.0-9=?A-Z^_`{|}~]+' . '@' . '[-!#$%&\'*+\\0-9=?A-Z^_`{|}~]+\.' . '[-!#$%&\'*+\\.0-9=?A-Z^_`{|}~]+$',$v)){
			return "メールアドレスの入力形式が正しくありません。";
		}elseif(!ereg("@",$v)){
			return "メールアドレスに「@」が含まれていません。";
		}else{
			return 0;
		}
	}
	//
	//
	//////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
	////	カタカナチェック	//////////////////////////////////////////////////////////
	//
	//
	
	### **** 全角カタカナチェック ****
	function Katakana (&$Value){
		if($Value){
			$Value = mb_convert_kana($Value,"KVCS");
		}else{
			return 2;
		}
		
		if(mbereg("[^ァ-ヴ,　,ー,（,）]",$Value)){
			return 1;
		}else{
			return 0;
		}
	}
	### 全角カタカナチェック（返り値変更）
	function Katakana2 (&$Value){
		if($Value){
			$Value = mb_convert_kana($Value,"KVCS");
		}else{
			return "を入力して下さい。";
		}
		
		if(mbereg("[^ァ-ヴ,　,ー,（,）]",$Value)){
			return "を全角カタカナで入力して下さい。";
		}else{
			return 0;
		}
	}
	//
	//
	//////////////////////////////////////////////////////////////////////////////////////
	
	
	
	////	数字チェック		//////////////////////////////////////////////////////////
	//
	//
	function Num (&$Value,$One=""){
		if($Value){
			$Value = mb_convert_kana($Value,"KVa");
		}else{
			return 2;
		}
		
		if($One){
			if(mbereg("[^0-9,$One]",$Value)){
				return 1;
			}else{
				return 0;
			}
		}else{
			if(!is_numeric($Value)){
				return 1;
			}else{
				return 0;
			}
		}
	}
	function Num2 (&$Value){
		if($Value){
			$Value = mb_convert_kana($Value,"KVa");
		}else{
			return 2;
		}
		
		if(!is_numeric($Value)){
			return "を半角数字で入力して下さい。";
		}else{
			return 0;
		}
	}
	//
	//
	/////////////////////////////////////////////////////////////////////////////////////
	
	
	
	////	日付チェック		//////////////////////////////////////////////////////////
	//
	//
	function dateemp($v){
		if($v==0){
			return "の記入して下さい。";
		}else{
			return 0;
		}
	}
	function datefmt($v){
		if(!$v){ return 0; }
		$d=date("Y-m-d");
		
		if(!ereg("([0-9]{4})[-|\/]([0-9]{1,2})[-|\/]([0-9]{1,2})",$v,$darr)){
			return "の入力形式が正しくありません。 (例. {$d})";
		}else{
			if($darr[2]>12){
				return "の月の形式が正しくありません。";
			}elseif($darr[3]>31){
				return "の日の形式が正しくありません。";
			}else{
				return 0;
			}
		}
	}
	//
	//
	/////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
	////	文字数チェック		//////////////////////////////////////////////////////////
	//
	//
	function StrNum($Value, $Min="", $Max=""){
		
		////    〜以上、〜以下
		if($Min && $Max){
			if($Max < mbstrlen($Value) || $Min > mbstrlen($Value)){
				return 1;
			}else{
				return 0;
			}

        ////    〜文字以下
		}elseif($Min && !$Max){
			if(mbstrlen($Value) < $Min){
				return 1;
			}else{
				return 0;
			}

        ////    〜文字以上
		}elseif($Max && !$Min){
			if(mbstrlen($Value) > $Max){
				return 1;
			}else{
				return 0;
			}
		}
	}
	
	###	(配列版)
	function Length($v, $c=array()){
		if(!$v || !$c){ return 0; }
		
		$Min=$c['min'];
		$Max=$c['max'];
		
		////    〜以上、〜以下
		if($Min && $Max){
			if($Max < mbstrlen($v) || $Min > mbstrlen($v)){
				if($Min==$Max){
					return "を" . $Min . "文字になるように入力して下さい。";
				}else{
					return "を" . $Min . "文字以上、" . $Max . "文字以内で入力して下さい。";
				}
			}else{
				return 0;
			}
			
        ////    〜文字以下
		}elseif($Min && !$Max){
			if(mbstrlen($v) < $Min){
				return "を" . $Min . "文字以内で入力して下さい。";
			}else{
				return 0;
			}

        ////    〜文字以上
		}elseif($Max && !$Min){
			if(mbstrlen($v) > $Max){
				return "を" . $Max . "文字以上で入力して下さい。";
			}else{
				return 0;
			}
		}
	}
	//
	//
	//////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
	
	
	
	### **** 配列の中にあるか ****
	function InSelect($Needle, $Array){
		if(!@in_array($Needle, $Array)){
			return 1;
		}else{
			return 0;
		}
	}
	
	
	
	
	
	
	////	エラー出力関連		//////////////////////////////////////////////////////////
	//
	//
	/* err message */
	function ErrEmp($val){
		return "「" . $val . "」をご記入ください。";
	}

	function ErrGaiji($val,$chr){
		return "「".$val."」の中に機種依存文字「".$chr."」が含まれています。";
	}

	function ErrHankaku($val){
		return "「" . $val . "」を半角英数字でご記入ください。";
	}
	
	function ErrMail1($val){
		return "「" . $val . "」に「@」が含まれていません。";
	}
	
	function ErrMail2($val){
		return "「" . $val . "」が不適切です。再度確認して下さい。";
	}
	
	function ErrKatakana($val){
		return "「" . $val . "」を全角カタカナでご記入ください。";
	}

	function ErrNum($val,$one=""){
		if(!$one){
			return "「" . $val . "」を半角数字でご記入ください。";
		}else{
			return "「" . $val . "」を半角数字と「" . $one . "」でご記入ください。";
		}
	}
	function ErrStrNum($val, $Min="", $Max=""){
		if($Max && $Min){
			if($Max == $Min){
				return "「" . $val . "」を" . $Min . "文字になるよう、ご記入ください。";
			}else{
				return "「" . $val . "」を" . $Min . "文字以上、" . $Max . "文字以内でご記入ください。";
			}
		}elseif($Max && !$Min){
			return "「" . $val . "」を" . $Max . "文字以内でご記入ください。";
		}elseif(!$Max && $Min){
			return "「" . $val . "」を" . $Min . "文字以上でご記入ください。";
		}
	}
	function ErrInSelect($val){
		return "「" . $val . "」が不適切です。再度確認して下さい。";
	}
	//
	//
	//////////////////////////////////////////////////////////////////////////////////////////
}
?>
