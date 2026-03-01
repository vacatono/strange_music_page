<?
// Read File
require_once('makeform.inc');


class MakeFormSql extends MakeForm {
	var $con;
	var $confirm;
	
	function MakeFormSql($con,$confirm){
		$this->con = $con;
		$this->confirm = $confirm;
	}

	### **** データを引き出してセレクトフォーム ****
	function SelectSql($Name="",$Default="",$Table="",$Id="",$Show="",$Where=""){
		if(!$Name or !$Table or !$Id or !$Show){ return false; }
		
		if($this->confirm){
			$sql = "select {$Id},{$Show} from {$Table} where ID='{$_POST[$Name]}'";
			$res = mysql_query($sql,$this->con) or die($sql);
			if(@mysql_num_rows($res)){
				echo mysql_result($res,0,$Show) . "\n";
				echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $this->SP_ENT($_POST[$Name]) . "\">\n";
			}else{
				echo "&nbsp;";
			}
		}else{
			$sql = "select {$Id},{$Show} from {$Table}{$Where}";
			$res = mysql_query($sql,$this->con) or die($sql);
			if(@mysql_num_rows($res) > 0){
				if(ereg(",",$Show)){ $Show = explode(",",$Show); }
				
				echo "<Select name=\"{$Name}\">\n";
				echo "<option value=\"\"></option>\n";
				
				while($Data = mysql_fetch_array($res)){
					if(@is_array($Show)){
						### **** 裏技用 ****
						if($Default == $Data[$Id]){
							echo "<option value=\"{$Data[$Id]}\" selected>";
						}else{
							echo "<option value=\"{$Data[$Id]}\">";
						}
						
						for($i=0; $i<count($Show); $i++){
							if($i != 0 and $Data[$Show[$i]]){ echo " --- "; }
							echo $Data[$Show[$i]];
						}
						echo "</option>\n";
					}else{
						if($Default == $Data[$Id]){
							echo "<option value=\"{$Data[$Id]}\" selected>{$Data[$Show]}</option>\n";
						}else{
							echo "<option value=\"{$Data[$Id]}\">{$Data[$Show]}</option>\n";
						}
					}
				}
				echo "</Select>\n";
				
			}
		}
	}
	
}
?>
