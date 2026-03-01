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
	var $range = 30;
	var $all;
	var $id;

	## コンストラクタ
	function Paging($all=0,$range="",$id=""){
		$this->all = $all;
		$this->id = $id;
		if($range){$this->range = $range;}
		if($_POST['start' . $id]){	$this->start = $_POST['start' . $id]; }
		if($_POST['range' . $id]){	$this->range = $_POST['range' . $id]; }
		if($_POST['next' . $id]){	$this->start += $this->range; }
		if($_POST['prev' . $id]){	$this->start -= $this->range; }
		
	#	 echo "start ---> " . $this->start."<Br>";
	#	 echo "range ---> " . $this->range."<Br>";
	#	 echo "all ---> " . $this->all."<Br>";
	}

	## 次のxx件
	function NextBtn($Opt=" style=\"background-color: white\""){
		if($this->all > $this->start + $this->range){
			print('<input type="submit" name="next' . $this->id . '" value=" 次の' . $this->range . '件 "' . $Opt . '>');
		}
	}
	
	## 前のxx件
	function PrevBtn($Opt=" style=\"background-color: white\""){
		if($this->start!=0){
			print('<input type="submit" name="prev' . $this->id . '" value=" 前の' . $this->range . '件 "' . $Opt) . '>';
		}
	}
	
	## HIDDENフィールド表示
	function MakeHidden(){
		print('<input type="hidden" name="start' . $this->id . '" value="' . $this->start . '">');
	#	print('<input type="hidden" name="range' . $this->id . '" value="' . $this->range . '">');
	}

	## 件数表示
	function ShowNumb($col=""){
		if($col){
			$fonts = '<font color="'.$col.'">';
			$fonte = '</font>';
		}
		if($this->all == 0){
			print("全0件");
		}elseif($this->all > ($this->start + $this->range)){
			print('全' . $fonts . number_format($this->all) . $fonte . '件中 ' . $fonts . ($this->start + 1) . $fonte . '〜' . $fonts . ($this->start + $this->range) . $fonte . '件表示');
		}else{
			print('全' . $fonts . number_format($this->all) . $fonte . '件中 ' . $fonts . ($this->start + 1) . $fonte . '〜' . $fonts . $this->all . $fonte . '件表示');
		}
	}

	## 表示範囲設定
	function ChangeRange($RangeAry=array("30","100","200")){
		
		echo "<Select name=\"range{$this->id}\" onChange=\"document.form.start.value=0;document.form.submit()\">\n";
		foreach($RangeAry as $Num){
			if($this->range == $Num){ echo "<option value=\"{$Num}\" selected>{$Num}</option>"; }else{ echo "<option value=\"{$Num}\">{$Num}</option>\n"; }
		}
		echo "</Select>\n";
	}
}

?>
