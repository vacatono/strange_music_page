<?
//	cart用 class
//	memo:
//

class Cart{
	
	//	member
	var $mode;			//	session or cookie?
	var $modename;		//	session name or cookie name.
	var $cartdata;		//	in cart
	
	
	//	construct
	function Cart($mode="session", $modename="carter"){
		
		$this->mode		=	$mode;
		$this->modename	=	$modename;
		
		//	初期設定
		$this->Loading();
	}
	
	//	変更 (num式)
	function Mod($Unique, $data=array()){
		
		if(!$data["num"] || ($data["num"] < 1)){
			$this->Del($Unique);
		}else{
			$this->Add($Unique, $data);
		}
	}
	
	//	変更 (既にあるものは削除し、ないものは取り入れ)
	function Mod2($Unique, $data=array()){
		if($this->cartdata){ foreach($this->cartdata as $id => $array){
			if($id == $Unique){
				$this->Del($Unique);
				$found = 1;
			}
		}}
		if(!$found){
			$this->Add($Unique, $data);
		}
		$this->Save();
	}
	
	//	一件追加
	function Add($Unique, $data=array()){
		$this->cartdata[$Unique] = $data;
		$this->Save();
	}
	
	//	一件削除
	function Del($Unique){
		unset($this->cartdata[$Unique]);
		$this->Save();
	}
	
	//	配列で還す
	function getCart(){ return $this->cartdata;
	}
	
	//	pre list
	function ShowList(){
		echo "<pre>\n";
		print_r($this->cartdata);
		echo "</pre>\n";
	}
	
	//	初期設定
	function Loading(){
		if($this->mode == "session"){
			session_start();
			$this->cartdata = $_SESSION[$this->modename];
		}elseif($this->mode == "cookie"){
			$this->cartdata = unserialize(stripslashes($_COOKIE[$this->modename]));
		}
	}
	
	//	セーブ
	function Save(){
		if($this->mode == "session"){
			$_SESSION[$this->modename] = $this->cartdata;
		}elseif($this->mode == "cookie"){
			setcookie($this->modename, serialize($this->cartdata), time()+3600);
		}
		return true;
	}
	
	//	セッションクリア
	function Clear(){
		if($this->mode == "session"){
			unset($_SESSION[$this->modename]);
			unset($this->cartdata);
			$this->Save();
		}elseif($this->mode == "cookie"){
			setcookie($this->modename, "", time()-3600);
		}
	}
}
?>
