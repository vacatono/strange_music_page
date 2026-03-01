<?
###########################################
#                                         #
#     Paging.inc                          #
#     2003.6.9 sugawara kei               #
#     何件〜何件表示                      #
#                                         #
###########################################

class Paging{
	var $start = 0;
	var $range = 50;
	var $all;

	## コンストラクタ
	function Paging($all=0,$range=""){
		$this->all = $all;
		if($range){$this->range = $range;}
		if($_POST[start]){	$this->start = $_POST[start]; }
		if($_POST[range]){	$this->range = $_POST[range]; }
		if($_POST[next]){	$this->start += $this->range; }
		if($_POST[prev]){	$this->start -= $this->range; }
		
	#	 echo "start ---> " . $this->start."<Br>";
	#	 echo "range ---> " . $this->range."<Br>";
	#	 echo "all ---> " . $this->all."<Br>";
	}

	## 次のxx件 (return式)		by kou (2004年 11月 27日 土曜日 13:41:41 JST)
	function retNextBtn($Opt=" style=\"background-color: white\""){
		if($this->all > $this->start + $this->range){
			return '<input type="submit" name="next" value=" 次の' . $this->range . '件 "' . $Opt . '>';
		}
	}
	
	## 前のxx件 (return式)		by kou (2004年 11月 27日 土曜日 13:41:41 JST)
	function retPrevBtn($Opt=" style=\"background-color: white\""){
		if($this->start!=0){
			return '<input type="submit" name="prev" value=" 前の' . $this->range . '件 "' . $Opt . '>';
		}
	}

	
	## 次のxx件
	function NextBtn($Opt=""){
		if($this->all > $this->start + $this->range){
			print '<input type="submit" name="next" value=" 次の' . $this->range . '件 "' . $Opt . '>';
		}
	}
	
	## 前のxx件
	function PrevBtn($Opt=""){
		if($this->start!=0){
			print '<input type="submit" name="prev" value=" 前の' . $this->range . '件 "' . $Opt . '>';
		}
	}

	## 両方
	function BothBtn($Opt=""){
		if($this->all <= $this->start + $this->range){
			$nextdis = " disabled";
		}
		if(!$this->start){
			$prevdis = " disabled";
		}
		echo "<input type=\"submit\" name=\"prev\" value=\"前の" . $this->range . "件\"".$Opt.$prevdis.">";
		echo "<input type=\"submit\" name=\"next\" value=\"次の" . $this->range . "件\"".$Opt.$nextdis.">";
	}
	
	## HIDDENフィールド表示
	function MakeHidden(){
		print('<input type="hidden" name="start" value="' . $this->start . '">');
	#	print('<input type="hidden" name="range" value="' . $this->range . '">');
	}

	## 件数表示
	function ShowNumb($col=""){
		if($col){
			$fonts = '<font color="'.$col.'">';
			$fonte = '</font>';
		}
		if($this->all == 0){
			print("全{$fonts}0{$fonte}件");
		}elseif($this->all > ($this->start + $this->range)){
			print('全' . $fonts . number_format($this->all) . $fonte . '件中 ' . $fonts . ($this->start + 1) . $fonte . '〜' . $fonts . ($this->start + $this->range) . $fonte . '件表示');
		}else{
			print('全' . $fonts . number_format($this->all) . $fonte . '件中 ' . $fonts . ($this->start + 1) . $fonte . '〜' . $fonts . $this->all . $fonte . '件表示');
		}
	}

	## 表示範囲設定
	function ChangeRange($RangeAry=array("50","100","200")){
		
		echo "<Select name=\"range\" onChange=\"document.form.start.value=0;document.form.submit()\">\n";
		foreach($RangeAry as $Num){
			if($this->range == $Num){ echo "<option value=\"{$Num}\" selected>{$Num}</option>"; }else{ echo "<option value=\"{$Num}\">{$Num}</option>\n"; }
		}
		echo "</Select>\n";
	}
	
	
	////	btnPtn1;
	function Ptn1($Opt=array()){
		
		//inicilization;
		$width			=	"100%";
		$range_array	=	array(50,100,150,200,300);
		$show_numb = 'blue';
		
		
		if($Opt['show_numb']){
			$show_numb = $Opt['show_numb'];
		}
		if($Opt['table_width']){
			$width = $Opt['table_width'];
		}
		if($Opt['range_array']){
			$range_array = $Opt['range_array'];
		}
		if($Opt['btn_class']){
			$opt = " class=\"" . $Opt['btn_class'] . "\"";
		}
		if($Opt['btn_style']){
			$opt = " style=\"" . $Opt['btn_class'] . "\"";
		}
		
		
		echo "<table border=0 cellpadding=0 cellspacing=0 width=\"{$width}\">\n";
		echo "<tr><td>\n";
		$this->ShowNumb($show_numb);
		echo " / ";
		$this->ChangeRange($range_array);
		echo "件ずつ表示</td>\n";
		echo "<td align=\"right\">";
		$this->BothBtn($opt);
		echo "</td>\n";
		echo "</tr>\n";
		echo "</table>\n";
	}
	
	////	btnPtn2;
	function Ptn2($Opt=array()){
	
		//inicilization;
		$width			=	"100%";

		if($Opt['table_width']){
			$width = $Opt['table_width'];
		}
		if($Opt['btn_class']){
			$opt = " class=\"" . $Opt['btn_class'] . "\"";
		}
		if($Opt['btn_style']){
			$opt = " style=\"" . $Opt['btn_class'] . "\"";
		}
		
		
		if($this->retNextBtn() || $this->retPrevBtn()){
			echo "<table border=0 cellpadding=0 cellspacing=0 width=\"{$width}\">\n";
			echo "<tr><td>\n";
			$this->PrevBtn($opt);
			echo "\n</td>\n<td align=\"right\">";
			$this->NextBtn($opt);
			echo "</td></tr>\n";
			echo "</table>\n";
		}
	}
	
	////	btnPtn3;
	function Ptn3($Opt=array()){
	
		//inicilization;
		$width			=	"100%";

		if($Opt['table_width']){
			$width = $Opt['table_width'];
		}
		if($Opt['btn_class']){
			$opt = " class=\"" . $Opt['btn_class'] . "\"";
		}
		if($Opt['btn_style']){
			$opt = " style=\"" . $Opt['btn_class'] . "\"";
		}
		
		if($this->retNextBtn() || $this->retPrevBtn()){
			echo "<table border=0 cellpadding=0 cellspacing=0 width=\"{$width}\">\n";
			echo "<td align=\"right\">";
			$this->PrevBtn($opt);
			$this->NextBtn($opt);
			echo "</td></tr>\n";
			echo "</table>\n";
		}
	}

	function AddSql(){
		return " limit {$this->start},{$this->range}";
	}
}
?>
