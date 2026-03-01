<?
class Sorter{
	
	// key Name
	var $KeyName;
	
	// Construct
	function Sorter($Name="Sorter"){
		$this->KeyName = $Name;
	}
	
	function Sql(){
		if($_POST[$this->KeyName]){
			return " order by {$_POST[$this->KeyName]}";
		}
	}
	
	function Key($Val, $Str="▲", $Color="white"){
		if($_POST[$this->KeyName] == $Val){
			echo "<font color=\"red\">" . $Str . "</font>";
		}else{
			echo "<a href=\"javascript:onClick=document.form." . $this->KeyName . ".value='" . $Val . "'; document.form.submit()\" style=\"color: " . $Color . "; text-decoration: none\">";
			echo $Str;
			echo "</a>";
		}
	}
	
	function KeyDesc($Val, $Str="▼", $Color="white"){
		
		// Order by Desc 用
		if($Val){ $Val = $Val . " desc"; }
		
		if($_POST[$this->KeyName] == $Val){
			echo "<font color=\"red\">" . $Str . "</font>";
		}else{
			echo "<a href=\"javascript:onClick=document.form." . $this->KeyName . ".value='" . $Val . "'; document.form.submit()\" style=\"color: " . $Color . "; text-decoration: none\">";
			echo $Str;
			echo "</a>";
		}
	}
	
	function Both($Val, $Color="white"){
		$this->Key($Val, "▲", $Color);
		$this->KeyDesc($Val, "▼", $Color);
	}
	
	
	
	//
	//	自由度アップ
	//
	function Key2($Val, $Opt=array(), $Str="▲"){
		
		//
		//	クリック前
		//
		if($Opt['before_class']){
			$beforeclass = " class=\"{$Opt['before_class']}\"";
		}
		if($Opt['before_style']){
			$beforestyle = " style=\"{$Opt['before_style']}\"";
		}else{
			$beforestyle = " style=\"color: white\"";
		}
		
		//
		//	クリック後
		//
		if($Opt['after_class']){
			$afterclass = " class=\"{$Opt['after_class']}\"";
		}
		if($Opt['after_style']){
			$afterstyle = " style=\"{$Opt['after_style']}\"";
		}else{
			$afterstyle = " style=\"color: red\"";
		}
		
		if($_POST[$this->KeyName] == $Val){
			echo "<span{$afterclass}{$afterstyle}>" . $Str . "</span>";
		}else{
			echo "<a href=\"javascript:onClick=document.form." . $this->KeyName . ".value='" . $Val . "'; document.form.submit()\"{$beforeclass}{$beforestyle}>";
			echo $Str;
			echo "</a>";
		}
	}
	//
	//	自由度アップ
	//
	function KeyDesc2($Val, $Opt=array(), $Str="▲"){
		
		//
		//	Order by Desc 用
		//
		if($Val){ $Val = $Val . " desc"; }
		
		
		//
		//	クリック前
		//
		if($Opt['before_class']){
			$beforeclass = " class=\"{$Opt['before_class']}\"";
		}
		if($Opt['before_style']){
			$beforestyle = " style=\"{$Opt['before_style']}\"";
		}else{
			$beforestyle = " style=\"color: white\"";
		}
		
		//
		//	クリック後
		//
		if($Opt['after_class']){
			$afterclass = " class=\"{$Opt['after_class']}\"";
		}
		if($Opt['after_style']){
			$afterstyle = " style=\"{$Opt['after_style']}\"";
		}else{
			$afterstyle = " style=\"color: red\"";
		}
		
		if($_POST[$this->KeyName] == $Val){
			echo "<span{$afterclass}{$afterstyle}>" . $Str . "</span>";
		}else{
			echo "<a href=\"javascript:onClick=document.form." . $this->KeyName . ".value='" . $Val . "'; document.form.submit()\"{$beforeclass}{$beforestyle}>";
			echo $Str;
			echo "</a>";
		}
	}
	
	//
	//	配列対応様
	//
	function Both2($Val, $Opt=array()){
		$this->Key2($Val, $Opt, "▲");
		$this->KeyDesc2($Val, $Opt, "▼");
	}

	function MakeHidden(){
		echo "<input type=\"hidden\" name=\"" . $this->KeyName . "\" value=\"" . $_POST[$this->KeyName] . "\">\n";
	}
}
?>
