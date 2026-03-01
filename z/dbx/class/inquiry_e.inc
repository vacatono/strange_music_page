<?
class SendMail {
	
	var $err;
	var $Mailok;
	
	function SP_ENT($Val){
		return htmlspecialchars(stripslashes($Val), ENT_QUOTES);
	}
	
	// Mail Encoding
	function str2mime($Str){
		if(mb_detect_encoding($Str) != "JIS"){
			$Str = mb_convert_encoding($Str,"JIS",mb_detect_encoding($Str));
		}
		return "=?ISO-2022-JP?B?" . base64_encode($Str) . "?=";
	}
	
	
	### **** お問い合わせフォーム表示 ****
	function ShowForm($Tbcol="",$Thcol="",$Tdcol="",$Loc="", $Border=""){ ?>
		<Br>
		<table border=<? if($Border){ echo $Border; }else{ echo "0"; } ?> cellpadding=2 cellspacing=1 width="100%"<? if($Tbcol){ echo " class=\"{$Tbcol}\""; } ?>>
		<tr>
		<th<? if($Thcol){ echo " class=\"{$Thcol}\""; } ?> width="20%" height=25 nowrap>Name</th>
		<td<? if($Tdcol){ echo " class=\"{$Tdcol}\""; } ?>>
			<? if($_POST[confirm]){ echo $this->SP_ENT($_POST[NAME]); ?><input type="hidden" name="NAME" value="<?= $this->SP_ENT($_POST[NAME]); ?>">
			<? }else{ ?><input type="text" name="NAME" value="<?= $this->SP_ENT($_POST[NAME]); ?>" size=60>
			<? } ?>
	    </td>
		</tr>
		<tr>
		<th<? if($Thcol){ echo " class=\"{$Thcol}\""; } ?> width="20%" height=25 nowrap>E-mail</th>
		<td<? if($Tdcol){ echo " class=\"{$Tdcol}\""; } ?>>
			<? if($_POST[confirm]){ echo $this->SP_ENT($_POST[E_MAIL]); ?><input type="hidden" name="E_MAIL" value="<?= $this->SP_ENT($_POST[E_MAIL]); ?>">
			<? }else{ ?><input type="text" name="E_MAIL" value="<?= $this->SP_ENT($_POST[E_MAIL]); ?>" size=60>
			<? } ?>
		</td>
		</tr>
		<tr>
		<th<? if($Thcol){ echo " class=\"{$Thcol}\""; } ?> width="20%" nowrap>Message</th>
		<td<? if($Tdcol){ echo " class=\"{$Tdcol}\""; } ?>>
			<? if($_POST[confirm]){ echo nl2br($this->SP_ENT($_POST[FAQ])); ?><input type="hidden" name="FAQ" value="<?= $this->SP_ENT($_POST[FAQ]); ?>">
			<? }else{ ?><textarea name="FAQ" rows=8 cols=70><?= $this->SP_ENT($_POST[FAQ]); ?></textarea>
			<? } ?>
		</td>
		</tr>
		</table>
		<Br>
		
		<table border=0 cellpadding=2 cellspacing=1 width="100%">
		<tr align="center">
		<? if(!$_POST[confirm]){
			if($Loc){ ?>
				<td width="50%"><input type="button" value="キャンセル" onClick="location.href='<?= $Loc; ?>'" style="background: white"></td>
				<td width="50%"><input type="submit" name="confirm" value="入力内容確認" style="background: white"></td>
			<? }else{ ?>
				<td><input type="submit" name="confirm" value="入力内容確認" style="background: white"></td>
			<? }
		}else{ ?>
			<td width="50%"><input type="submit" name="back" value="戻&nbsp;&nbsp;&nbsp;&nbsp;る" style="background: white"></td>
			<td width="50%"><input type="submit" name="send" value="入力内容送信" style="background: white"></td>
		<? } ?>
		</tr>
		</table>
	<? }
	
	
	### **** 内容チェック ****
	function CheckForm(){
		if(!$_POST[confirm]){ return false; }
		
		if(!$_POST[NAME]){ $this->err[] = "Please input Name.";}
	    if(!$_POST[E_MAIL]){ $this->err[] = "Please input E-mail.";
		}else{
			if(!ereg("@",$_POST[E_MAIL])){ $this->err[] = "メールアドレスに「@」が含まれていません。";
			}elseif(!eregi('^[-!#$%&\'*+\\.0-9=?A-Z^_`{|}~]+' . '@' . '[-!#$%&\'*+\\0-9=?A-Z^_`{|}~]+\.' . '[-!#$%&\'*+\\.0-9=?A-Z^_`{|}~]+$',$_POST[E_MAIL])){
				$this->err[] = "メールアドレスが不適切です。再度ご確認ください。";
			}
		}
		if(!$_POST[FAQ]){ $this->err[] = "Please input Message."; }
		if(count($this->err)){
			unset($_POST[confirm]);
		}
	}
	
	
	function Message(){
		if(!$_POST[confirm] and count($this->err)){ ?>
			<Div style="width: 100%; background-color: white; line-height: 20px; text-align: left; border: 1px solid black; padding: 20px">
			記入項目にエラーが発生しました。以下を参照してください。<Br>
			<br>
			<Div style="font-size: 9pt; color: #ff0000;"> 
				<? for($i=0;$i<count($this->err);$i++){ echo "■&nbsp;&nbsp;" . $this->err[$i] . "<Br>\n"; } ?>
			</Div>
			</Div>
			<Br>
		<? }elseif(!$_POST[confirm] and !count($this->err)){ ?>
			<Div style="width: 100%; background-color: white; line-height: 20px; text-align: left; border: 1px solid black; padding: 20px">
			Please fill your Name, Mail Address and Contents then press SEND button.<br>
			<br>
			Password :<br>
			Please fill your ID and Mail Address then press SEND button.<Br>
			<br>
			</Div>
		<? }elseif($_POST[confirm] and !count($this->err)){ ?>
			<Br>
			<Div style="width: 100%; background-color: white; line-height: 20px; text-align: left; border: 1px solid black; padding: 20px">
			下記の内容で送信されます。<br>
			よろしければ「入力内容送信」ボタンをクリックして下さい。<br>
			変更個所があれば、「戻る」ボタンをクリックして下さい。</font>
			</Div>
		<? }elseif($_POST[send]){ ?>
			<br>
		<? }
	}

	function SendForm($Mailer="webmaster@japal.co.jp",$Subject="ジャパール"){
		### **** メール送信 ****
		
		if($_POST[send]){
			
			$MailTo = $Mailer;
			$MailSubject = "{$Subject}お問い合わせメール";
			$MailContents = "----------------------------------------------------\n";
			$MailContents .= "\n";
			$MailContents .= "{$Subject}からお問い合わせメールです。\n";
			$MailContents .= "\n";
			$MailContents .= "　受付日時　　　　：" . date("Y-m-d H:i") . "\n";
			$MailContents .= "\n";
			$MailContents .= "----------------------------------------------------\n";
			$MailContents .= "\n";
			$MailContents .= "■お客様データ\n";
			$MailContents .= "\n";
			$MailContents .= "　氏名　　　　　：" . $_POST[NAME] . "\n";
			$MailContents .= "　メールアドレス：" . $_POST[E_MAIL] . "\n";
			$MailContents .= "\n";
			$MailContents .= "----------------------------------------------------\n";
			$MailContents .= "\n";
			$MailContents .= "■お問い合わせ内容\n";
			$MailContents .= "\n";
			$MailContents .= "　$_POST[FAQ]\n";
			$MailContents .= "\n";
			$MailContents .= "----------------------------------------------------\n";
			$MailContents .= "\n";
			
			$MailHeaders = "From: {$_POST[E_MAIL]}\n";
			$MailHeaders .= "Reply-To: {$Mailer}\n";
			$MailHeaders .= "X-Mailer: PHP/" . phpversion() . "\n";
			$MailReturn = "-f" . $Mailer;
			
			$MailSubject = mb_convert_encoding($MailSubject,"JIS","EUC");
			$MailContents = mb_convert_encoding($MailContents,"JIS","EUC");
			
			if(mail($MailTo,$this->str2mime($MailSubject),$MailContents,$MailHeaders,$MailReturn)){
				$this->Mailok  = 1;
			}
		}
	}

	function After($Loc=""){
		if($_POST[send] and $this->Mailok){
			echo "alert(\"お問い合わせ内容が管理者宛に送信されました。\");\n";
			if($Loc){ echo "location.href=\"{$Loc}\";\n";
			}else{ echo "location.href=\"{$_REQUEST[PHP_SELF]}\";\n";
			}
		}elseif($_POST[send] and !$this->Mailok){
			echo "alert(\"問い合わせ内容を送信のに失敗しました。\\n再度ご確認の上「送信」ボタンを押してください。\");\n";
			if($Loc){ echo "location.href=\"{$Loc}\";\n";
			}else{ echo "location.href=\"{$_REQUEST[PHP_SELF]}\";\n";
			}
		}
	}
}
?>
