<?
class cForm {

	
	//	escape
	function SP_ENT($VAL){
		return htmlspecialchars(stripslashes($VAL), ENT_QUOTES);
	}
	
	//	配列対応
	function ReturnValue($Name=""){
		if(ereg("(^[^\[]+)(.*)", $Name, $Paturn)){
			
			$value[0] = $Paturn[1];
			if($Paturn[2]){
				$Paturn[2] = ereg_replace("^\[", "", ereg_replace("\]$", "", $Paturn[2]));
				$value = array_merge($value, split("\]\[",$Paturn[2]));
			}
			
			$bool = $_POST;
			foreach($value as $val){
				$bool = $bool[$val];
			}
			return $bool;
		}else{
			return false;
		}
	}
	
	////	Text
	function Text($confirm="", $Name="", $Default="", $Opt=array()){
		if(!$Name){
			return false;
		}
		
		switch($Opt['set']){
			case 'act':
				$Opt2['style']		=	"ime-mode: active";
			break;
			case 'dis':
				$Opt2['style']		=	"ime-mode: disabled";
			break;
			case 'dis2':
				$Opt2['style']		=	"ime-mode: disabled; text-align: right";
			break;
			case 'nums':
				$Opt2['style']		=	"ime-mode: disabled; text-align: right";
				$Opt2['size']		=	10;
				$Opt2['maxlength']	=	8;
			break;
			case 'code':
				$Opt2['style']		=	"ime-mode: disabled";
				$Opt2['size']		=	20;
				$Opt2['maxlength']	=	240;
			break;
			case 'email':
				$Opt2['style']		=	"ime-mode: disabled";
				$Opt2['size']		=	"40";
				$Opt2['maxlength']	=	"240";
			break;
			case 'price':
				$Opt2['style'] = "ime-mode: disabled; text-align: right";
				$Opt2['size'] = 12;
				$Opt2['maxlength'] = 8;
			break;
			case 'name':
				$Opt2['style'] = "ime-mode: active";
				$Opt2['size'] = "40";
				$Opt2['maxlength'] = "240";
			break;
		}
		
		if($confirm){
			if(strlen($val = cForm::ReturnValue($Name))){
				
				//	price用;
				if($Opt['set']=='price'){
					echo "\\" . @number_format($val);
				
				//	数量用 (nums)
				//
				}elseif($Opt['set']=="nums"){
					echo @number_format($val);
					
				//	他;
				}else{
					echo cform::SP_ENT($val);
				}
			}else{
				echo "&nbsp;";
			}
			cForm::Hidden($Name, $val);
		}else{
			
			$Opt = array_merge($Opt2,$Opt);

			//	input option
			if($Opt['size']){			$Option = " size=\"{$Opt[size]}\"";				}
			if($Opt['maxlength']){		$Option .= " maxlength=\"{$Opt[maxlength]}\"";	}
			
			//	style,javascript option
			if($Opt[style]){			$Option .= " style=\"{$Opt[style]}\"";			}
			if($Opt["class"]){			$Option .= " class=\"" . $Opt["class"] . "\"";	}
			if($Opt[onclick]){			$Option .= " onClick=\"{$Opt[onclick]}\"";		}
			if($Opt[onchange]){			$Option .= " onChange=\"{$Opt[onchange]}\"";	}
			if($Opt[onfocus]){			$Option .= " onFocus=\"{$Opt[onfocus]}\"";	}
			if($Opt['onblur']){			$Option .= " onblur=\"" . $Opt['onblur'] . "\""; }
			if($Opt[id]){				$Option .= " id=\"{$Opt[id]}\"";				}

			//	other
			if($Opt[readonly]){			$Option .= " readonly";							}
			if($Opt[disabled]){			$Option .= " disabled";							}
			if($Opt[istyle]){			$Option .= " istyle=\"{$Opt[istyle]}\""; 		}
			
			//	echo
			echo "<input type=\"text\" name=\"{$Name}\" value=\"" . cForm::SP_ENT($Default) . "\"{$Option}>";
		}
	}
		
	////	Password
	function Password($confirm="", $Name="", $Default="", $Opt=array()){
		if(!$Name){
			return false;
		}
		
		if($confirm){
			if($val = cForm::ReturnValue($Name)){
				echo str_repeat("*", strlen($val)) . "\n";
			}else{
				echo "&nbsp;";
			}
			cForm::Hidden($Name, $val);
		}else{
			
			//	input option
			if($Opt[size]){				$Option = " size=\"{$Opt[size]}\"";					}
			if($Opt[maxlength]){		$Option .= " maxlength=\"{$Opt[maxlength]}\"";		}
			
			//	style,javascript option
			if($Opt["class"]){			$Option .= " class=\"" . $Opt["class"] . "\"";		}
			if($Opt[style]){			$Option .= " style=\"{$Opt[style]}\"";				}
			if($Opt[onclick]){			$Option .= " onClick=\"{$Opt[onclick]}\"";			}
			if($Opt[onchange]){			$Option .= " onChange=\"{$Opt[onchange]}\"";		}
			if($Opt[id]){				$Option .= " id=\"{$Opt[id]}\"";					}
			
			//	other
			if($Opt[readonly]){			$Option .= " readonly";							}
			if($Opt[disabled]){			$Option .= " disabled";							}
			
			//	echo
			echo "<input type=\"password\" name=\"{$Name}\" value=\"" . cForm::SP_ENT($Default) . "\"{$Option}>\n";
		}
	}
	
	////	Textarea
	function Textarea($confirm="", $Name="", $Default="", $Opt=array()){
		if(!$Name){ return false; }
			
		if($confirm){
			if($val = cForm::ReturnValue($Name)){
				echo nl2br(cForm::SP_ENT($val));
			}else{
				echo "&nbsp;\n";
			}
			
			cForm::Hidden($Name, $val);
		}else{
			
			//	input option
			if($Opt[cols]){				$Option = " cols=\"{$Opt[cols]}\"";					}
			if($Opt[rows]){				$Option .= " rows=\"{$Opt[rows]}\"";				}
			
			//	style,javascript option
			if($Opt["class"]){			$Option .= " class=\"" . $Opt["class"] . "\"";		}
			if($Opt[style]){			$Option .= " style=\"{$Opt[style]}\"";				}
			if($Opt[onclick]){			$Option .= " onClick=\"{$Opt[onclick]}\"";			}
			if($Opt[onchange]){			$Option .= " onChange=\"{$Opt[onchange]}\"";		}
			if($Opt[id]){				$Option .= " id=\"{$Opt[id]}\"";					}
			
			//	other
			if($Opt[readonly]){			$Option .= " readonly";								}
			if($Opt[disabled]){			$Option .= " disabled";								}
			
			//	echo
			echo "<textarea name=\"{$Name}\"{$Option}>" . cForm::SP_ENT($Default) . "</textarea>\n";
		}
	}

	
	////	Radio button
	function Radio($confirm="", $Name="", $Default="", $DataHash=array(), $Opt=array(), $Table=array()){
		if(!$Name){
			return false;
		}
		
		if($confirm){
			if($val = cForm::ReturnValue($Name)){
				echo $DataHash[$val];
			}else{
				echo "&nbsp;\n";
			}
			cForm::Hidden($Name, $val);
		}else{
			//	setting
			$cnt = 0;
			
			//
			//	template;
			//
			switch($Opt['set']){
				case 'tabzero':
					$Table['table_padding'] = 0;
					$Table['table_spacing'] = 0;
				break;
			}
			
			
			//	table
			if($Table[table_width]){				$Ta .= " width=\"{$Table[table_width]}\"";				}
			if(strlen($Table[table_border])){		$Ta .= " border=\"{$Table[table_border]}\"";			}
			if(strlen($Table[table_padding])){		$Ta .= " cellpadding=\"{$Table[table_padding]}\"";		}
			if(strlen($Table[table_spacing])){		$Ta .= " cellspacing=\"{$Table[table_spacing]}\"";		}
			if($Table[table_class]){				$Ta .= " class=\"{$Table[table_class]}\"";				}
			if($Table[table_style]){				$Ta .= " style=\"{$Table[table_style]}\"";				}

			//	tr
			if($Table[tr_class]){			$Tr .= " class=\"{$Table[tr_class]}\"";					}
			if($Table[tr_style]){			$Tr .= " style=\"{$Table[tr_style]}\"";					}
			
			//	td
			if($Table[td_class]){			$Td .= " class=\"{$Table[td_class]}\"";					}
			if($Table[td_style]){			$Td .= " style=\"{$Table[td_style]}\"";					}
			if($Opt['nowrap']){				$Td .= " nowrap";										}
			
			//	width
			if($Table['td_width']){
				$width = " width=\"" . $Table['td_width'] . "\"";
			}elseif($Opt[cols]){
				$width = " width=\"" . round((100/$Opt[cols]),3) . "%\"";
			}
			
			//	style,javascript option
			if($Opt[style]){			$Option .= " style=\"{$Opt[style]}\"";				}
			if($Opt["class"]){			$Option .= " class=\"" . $Opt["class"] . "\"";		}
			if($Opt[onclick]){			$Option .= " onClick=\"{$Opt[onclick]}\"";			}
			if($Opt[onchange]){			$Option .= " onChange=\"{$Opt[onchange]}\"";		}
			# if($Opt[id]){				$Option .= " id=\"{$Opt[id]}\"";					}
			
			//	other
			if($Opt[readonly]){			$Option .= " readonly";								}
			if($Opt[disabled]){			$Option .= " disabled";								}
			
			if($Opt["default"]){		$StartCheck = 1;									}
			
			
			//	text options;
			if($Opt["txt_style"]){
				$TxtOption .= " style=\"".$Opt["txt_style"]."\"";
			}
			
			
			
			//	echo
			echo "<table{$Ta}>\n";
			foreach($DataHash as $val => $show){
				if($cnt%$Opt[cols] == 0){ echo "<tr{$Tr}>\n"; }
				
				echo "<td{$width}{$Td}>\n";
				if($Default == $val || ($StartCheck && !$Default && $cnt == 0)){
					echo "<input type=\"radio\" name=\"{$Name}\" value=\"" . $val . "\" id=\"{$Name}_{$cnt}\" checked{$Option}>\n";
				}else{
					echo "<input type=\"radio\" name=\"{$Name}\" value=\"" . $val . "\" id=\"{$Name}_{$cnt}\"{$Option}>\n";
				}
				echo "<label for=\"{$Name}_{$cnt}\"{$TxtOption}>" . $show . "</label>\n";
				echo "</td>\n";
				
				if($cnt%$Opt[cols] == ($Opt[cols] - 1)){ echo "</tr>\n"; }
				$cnt++;
			}
			if($cnt%$Opt[cols] == ($Opt[cols] - 1)){ print('</tr>'); }
			echo "</table>\n";
		}
	}
	
	
	////	checkbox
	function Checkbox($confirm="", $Name="", $Default="", $DataHash=array(), $Opt=array(), $Table=array()){
		if(!$Name){
			return false;
		}
		//	table
		if($Table[table_width]){		$Ta .= " width=\"{$Table[table_width]}\"";				}
		if(strlen($Table[table_border])){		$Ta .= " border=\"{$Table[table_border]}\"";			}
		if(strlen($Table[table_padding])){		$Ta .= " cellpadding=\"{$Table[table_padding]}\"";		}
		if(strlen($Table[table_spacing])){		$Ta .= " cellspacing=\"{$Table[table_spacing]}\"";		}
		if($Table[table_class]){		$Ta .= " class=\"{$Table[table_class]}\"";				}
		if($Table[table_style]){		$Ta .= " style=\"{$Table[table_style]}\"";				}
		
		//	tr
		if($Table[tr_class]){			$Tr .= " class=\"{$Table[tr_class]}\"";					}
		if($Table[tr_style]){			$Tr .= " style=\"{$Table[tr_style]}\"";					}
		
		//	td
		if($Table[td_class]){			$Td .= " class=\"{$Table[td_class]}\"";					}
		if($Table[td_style]){			$Td .= " style=\"{$Table[td_style]}\"";					}
		if($Opt['nowrap']){				$Td .= " nowrap";										}
		
		//	width
		if($Table['td_width']){
			$width = " width=\"" . $Table['td_width'] . "\"";
		}elseif($Opt[cols]){
			$width = " width=\"" . round((100/$Opt[cols]),3) . "%\"";
		}
		
		//	カンマ区切りのデータを配列に
		if(!is_array($Default)){
			$Default = explode(",",$Default);
		}
		
		//	カンマ区切りのデータを配列に
		if(!is_array($_POST[$Name])){
			$_POST[$Name] = explode(",",$_POST[$Name]);
		}
		
		if($confirm){
			
			if(($rData = cForm::ReturnValue($Name)) && $rData[0]!=""){
				
				echo "<table{$Ta}>\n";
				foreach($rData as $val){
					if($cnt%$Opt[cols] == 0){ echo "<tr{$Tr}>\n"; }
					echo "<td{$width}{$Td}>{$DataHash[$val]}</td>\n";
					if($cnt%$Opt[cols] == ($Opt[cols] - 1)){ echo "</tr>\n"; }
					$cnt ++;
				}
				for($i=0; $i<($Opt[cols] - ($cnt%$Opt[cols])); $i++){
					echo "<td{$width}{$Td}>&nbsp;</td>\n";
				}
				if($cnt%$Opt[cols] == ($Opt[cols] - 1)){ print('</tr>'); }
				echo "</table>";
				
			}else{ echo "&nbsp;";
			}
			cForm::Hidden($Name, @join(",", $rData));
			
		}else{
			//	setting
			$cnt = 0;
			
			//	style,javascript option
			if($Opt[style]){			$Option .= " style=\"{$Opt[style]}\"";						}
			if($Opt[onclick]){			$Option .= " onClick=\"{$Opt[onclick]}\"";					}
			# if($Opt[id]){				$Option .= " id=\"{$Opt[id]}\"";							}
			
			//	other
			if($Opt[readonly]){			$Option .= " readonly";										}
			if($Opt[disabled]){			$Option .= " disabled";										}
			
			//	Default data setting
			if(!is_array($Default) && ereg(",", $Default)){
				$Default = explode(",", $Default);
			}
			
			echo "<table{$Ta}>\n";
			foreach($DataHash as $val => $show){
				if($cnt%$Opt[cols] == 0){ echo "<tr{$Tr}>\n"; }
				echo "<td{$width}{$Td}>\n";
				if(@in_array($val, $Default)){
					echo "<input type=\"checkbox\" name=\"{$Name}[]\" value=\"{$val}\" id=\"{$Name}_{$cnt}\" checked{$Option}>\n";
				}else{
					echo "<input type=\"checkbox\" name=\"{$Name}[]\" value=\"{$val}\" id=\"{$Name}_{$cnt}\"{$Option}>\n";
				}
				echo "<label for=\"{$Name}_{$cnt}\">{$show}</label>\n";
				echo "</td>\n";
				if($cnt%$Opt[cols] == ($Opt[cols] - 1)){
					echo "</tr>\n"; $endflag=1;
				}else{
					unset($endflag);
				}
				
				$cnt++;
			}
			if(!$endflag){
				for($i=0; $i<($Opt[cols] - ($cnt%$Opt[cols])); $i++){
					echo "<td{$width}{$Td}>&nbsp;</td>\n";
				}
				if($cnt%$Opt[cols] == ($Opt[cols] - 1)){ print('</tr>'); }
			}
			echo "</table>\n";
		}
	}
	function Checkbox0($confirm="",$Name="",$Default="",$value="1"){
		if($confirm){
			if($val=cform::ReturnValue($Name)){
				print("<input type=\"hidden\" name=\"{$Name}\" value=\"{$value}\">\n");
			}else{
				print("&nbsp;");
			}
		}else{
			if($val=cform::ReturnValue($Name)){
				print("<input type=\"checkbox\" name=\"{$Name}\" value=\"{$value}\" checked>\n");
			}else{
				print("<input type=\"checkbox\" name=\"{$Name}\" value=\"{$value}\">\n");
			}
		}
	}
	function Radio0($conf="",$name="",$def="",$hash=array(),$opt=array()){
		if($conf){
			if($val = cform::ReturnValue($name)){
				print($hash[$val]);
			}else{
				print("&nbsp;\n");
			}
			cform::Hidden($name,$val);
		}else{
            $cnt = 0;
            foreach($hash as $k => $v){
                $cnt++;
                if($def==$k || (!$def && $cnt==0)){
                    print('<input type="radio" name="'.$name.'" value="'.$k.'" id="'.$name.$k.'" checked>');
                }else{
                    print('<input type="radio" name="'.$name.'" value="'.$k.'" id="'.$name.$k.'">');
                }
                print('<label for="'.$name.$k.'">'.$v.'</label>');
				print($opt['sep']);
            }
		}
	}
	
	
	////	Select
	function Select($confirm="", $Name="", $Default="", $DataHash=array(), $Opt=array()){
		
		if($confirm){
			if($val = cForm::ReturnValue($Name)){
				echo $DataHash[$val];
			}else{
				echo "&nbsp;";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . cForm::SP_ENT($val) . "\">\n";
		}else{
			
			//	setting
			if($Opt[nodata]){			$nodata = 1;										}
			
			//	input option
			if($Opt[size]){				$Option = " size=\"{$Opt[size]}\"";					}
			
			//	style,javascript option
			if($Opt[style]){			$Option .= " style=\"{$Opt[style]}\"";				}
			if($Opt["class"]){			$Option .= " class=\"" . $Opt["class"] . "\"";		}
			if($Opt[onclick]){			$Option .= " onClick=\"{$Opt[onclick]}\"";			}
			if($Opt[onchange]){			$Option .= " onChange=\"{$Opt[onchange]}\"";		}
			if($Opt[id]){				$Option .= " id=\"{$Opt[id]}\"";					}
			
			//	other
			if($Opt[readonly]){			$Option .= " readonly";								}
			if($Opt[disabled]){			$Option .= " disabled";								}
			
			//	echo
			echo "<select name=\"{$Name}\"{$Option}>\n";
			if($nodata){ echo "<option value=\"\"></option>\n"; }
			foreach($DataHash as $val => $show){
				if($Default == $val){
					echo "<option value=\"{$val}\" selected>{$show}</option>\n";
				}else{
					echo "<option value=\"{$val}\">{$show}</option>\n";
				}
			}
			echo "</Select>\n";
		}
	}
	
	////	Date
	function Date($confirm="", $Name="", $Default="" ,$Opt=""){
		//	setting
		if(strlen($Opt[min])){		$min = $Opt[min]; }else{ $min = date("Y");		}
		if(strlen($Opt[max])){		$max = $Opt[max]; }else{ $max = date("Y");		}
		if($Opt[show]){				$show = $Opt[show];								}
		if($Opt[nodata]){			$nodata = 1;									}
		
		//	input option
		if($Opt[size]){				$Option = " size=\"{$Opt[size]}\"";					}
		
		//	style,javascript option
		if($Opt[style]){			$Option .= " style=\"{$Opt[style]}\"";				}
		if($Opt[onclick]){			$Option .= " onClick=\"{$Opt[onclick]}\"";			}
		if($Opt[onchange]){			$Option .= " onChange=\"{$Opt[onchange]}\"";		}
		if($Opt[id]){				$Option .= " id=\"{$Opt[id]}\"";					}
		
		//	other
		if($Opt[readonly]){			$Option .= " readonly";								}
		if($Opt[disabled]){			$Option .= " disabled";								}
		
		
		if($confirm){
			if($val = cForm::ReturnValue($Name)){
				if($Opt['absflag']){
					echo abs($val) . $Opt[show];
				}else{
					echo $val . $Opt[show];
				}
			}else{
				echo "&nbsp;";
			}
			cForm::Hidden($Name, $val);
		}else{
			echo "<select name=\"{$Name}\"{$Option}>\n";
			if($nodata){
				echo "<option value=\"\"></option>\n";
			}
			
			if($max >= $min){
				for($i=$min; $i<=$max; $i++){
					if(strlen($i)==1){
						$showi = "&nbsp;&nbsp;" . $i;
					}else{
						$showi = $i;
					}
					
					if($Default == $i){
						echo "<option value=\"{$i}\" selected>{$showi}{$show}</option>\n";
					}else{
						echo "<option value=\"{$i}\">{$showi}{$show}</option>\n";
					}
				}
			}else{
				for($i=$max; $i>=$min; $i--){
					if(strlen($i)==1){
						$showi = "&nbsp;&nbsp;" . $i;
					}else{
						$showi = $i;
					}
					
					if($Default == $i){
						echo "<option value=\"{$i}\" selected>{$showi}{$show}</option>\n";
					}else{
						echo "<option value=\"{$i}\">{$showi}{$show}</option>\n";
					}
				}
			}
			echo "</Select>\n";
		}
	}
	

	

	////	Date (Y-m-d)
	function GroupDate($confirm="", $Name="", $Default="", $Opt=""){

		
		$aopt = array();	//	オプション配列
		
		//	初期値
		if($Opt[yearmin]){		$YearMin = $Opt[yearmin];		}else{	$YearMin = date("Y");		}
		if($Opt[yearmax]){		$YearMax = $Opt[yearmax];		}else{	$YearMax = date("Y");		}
		if($Opt[nodata]){		$nodata = 1;					}

		if(!$Default){			
			if($nodata){
				$Default = "";
			}else{
				$Default = date("Y-m-d");
			}
		}

		if($Opt[size]){			$size = $Opt[size];				}
		if($Opt[show] == "jp"){
			$Yopt = "年";
			$Mopt = "月";
			$Dopt = "日";
		}elseif($Opt[show] == "en"){
			$Yopt = "/";
			$Mopt = "/";
			$Dopt = "/";
		}
		if($Opt[onchange]){	$aopt[onchange] = $Opt[onchange]; }
		if($Opt[disabled]){	$aopt[disabled] = $Opt[disabled]; }
		
		if(cForm::ReturnValue($Name."Y") || cForm::ReturnValue($Name."M") || cForm::ReturnValue($Name."D"))
		{
			$DefY = cForm::ReturnValue($Name."Y");
			$DefM = cForm::ReturnValue($Name."M");
			$DefD = cForm::ReturnValue($Name."D");
		}else{
			list($DefY,$DefM,$DefD) = split("-",$Default);
		}
		
		
		if($confirm){
			if($nodata && !abs($DefY) && !abs($DefM) && !abs($DefD)){
				
			}elseif($Opt[show]){
				print($DefY.$Yopt." ".$DefM.$Mopt." ".$DefD.$Dopt);
			}else{
				print($DefY."/".$DefM."/".$DefD);
			}
			
			cForm::Hidden($Name."Y", $DefY); 
			cForm::Hidden($Name."M", $DefM);
			cForm::Hidden($Name."D", $DefD);
			cForm::Hidden($Name, $DefY.'-'.sprintf("%02d",$DefM).'-'.sprintf("%02d",$DefD));
			
		}else{
			//	Year
			cForm::Date(0, $Name."Y", $DefY, array("min"=>$YearMin, "max"=>$YearMax, "show"=>$Yopt, "nodata"=>$nodata, "size"=>$size)+$aopt); 
			
			//	Month
			cForm::Date(0, $Name."M", $DefM, array("min"=>1, "max"=>12, "show"=>$Mopt, "nodata"=>$nodata, "size"=>$size)+$aopt);
			
			//	Day
			cForm::Date(0, $Name."D", $DefD, array("min"=>1, "max"=>31, "show"=>$Dopt, "nodata"=>$nodata, "size"=>$size)+$aopt);
			
			//	date;
			cForm::Hidden($Name, $DefY.'-'.sprintf("%02d",$DefM).'-'.sprintf("%02d",$DefD));
		}
	}

	//	GroupDateのText版
	function GroupDateText($confirm="", $Name="", $Default="", $Opt=""){

		
		$aopt = array();	//	オプション配列
		
		//	初期値
		if($Opt[nodata]){		$nodata = 1;					}

		if(!$Default){			
			if($nodata){
				$Default = "";
			}else{
				$Default = date("Y-m-d");
			}
		}

		if($Opt[size]){			$size = $Opt[size];				}
		if($Opt[show] == "jp"){
			$Yopt = "年";
			$Mopt = "月";
			$Dopt = "日";
		}elseif($Opt[show] == "en"){
			$Yopt = "/";
			$Mopt = "/";
			$Dopt = "/";
		}
		if($Opt[onchange]){	$aopt[onchange] = $Opt[onchange]; }
		if($Opt[disabled]){	$aopt[disabled] = $Opt[disabled]; }
		
		if(cForm::ReturnValue($Name."Y") || cForm::ReturnValue($Name."M") || cForm::ReturnValue($Name."D")){
			$DefY = cForm::ReturnValue($Name."Y");
			$DefM = cForm::ReturnValue($Name."M");
			$DefD = cForm::ReturnValue($Name."D");
		}else{
			list($DefY,$DefM,$DefD) = split("-",$Default);
			if(strlen($DefD)>2){
				$DefD = substr($DefD,0,2);
			}
		}
		
		
		if($confirm){
			if($nodata && !abs($DefY) && !abs($DefM) && !abs($DefD)){
				
			}elseif($Opt[show]){
				print($DefY.$Yopt." ".$DefM.$Mopt." ".$DefD.$Dopt);
			}else{
				print($DefY."/".$DefM."/".$DefD);
			}
			
			cForm::Hidden($Name."Y", $DefY); 
			cForm::Hidden($Name."M", $DefM);
			cForm::Hidden($Name."D", $DefD);
			cForm::Hidden($Name, $DefY.'-'.sprintf("%02d",$DefM).'-'.sprintf("%02d",$DefD));
			
		}else{
			//	Year
			cForm::Text(0, $Name."Y", $DefY, array("size"=>"5","maxlength"=>"4","style"=>"text-align: right; ime-mode: disabled")+$aopt); 
			print($Yopt);
			
			//	Month
			cForm::Text(0, $Name."M", $DefM, array("size"=>"3","maxlength"=>"2","style"=>"text-align: right; ime-mode: disabled")+$aopt); 
			print($Mopt);
			
			//	Day
			cForm::Text(0, $Name."D", $DefD, array("size"=>"3","maxlength"=>"2","style"=>"text-align: right; ime-mode: disabled")+$aopt); 
			print($Dopt);
			
			//	date;
			cForm::Hidden($Name, $DefY.'-'.$DefM.'-'.$DefD);
		}
	}
	
	//	GroupDateのText版　の配列版
	function GroupDateText2($confirm="", $Name="", $Default="", $Opt=""){

		//	配列[]の対応
		if(preg_match("/(.+?)\[(.+?)\]/",$Name,$reg)){
			$ak = $reg[2];
			$NameY = $reg[1]."Y[".$ak."]";
			$NameM = $reg[1]."M[".$ak."]";
			$NameD = $reg[1]."D[".$ak."]";
			$Name = $reg[1]."[".$ak."]";
		}else{
			$NameY = $Name."Y";
			$NameM = $Name."M";
			$NameD = $Name."D";
		}

		
		$aopt = array();	//	オプション配列
		
		//	初期値
		if($Opt[nodata]){		$nodata = 1;					}

		if(!$Default){			
			if($nodata){
				print("nodef");
				$Default = "";
			}else{
				$Default = date("Y-m-d");
			}
		}

		if($Opt[size]){			$size = $Opt[size];				}
		if($Opt[show] == "jp"){
			$Yopt = "年";
			$Mopt = "月";
			$Dopt = "日";
		}elseif($Opt[show] == "en"){
			$Yopt = "/";
			$Mopt = "/";
			$Dopt = "/";
		}
		if($Opt[onchange]){	$aopt[onchange] = $Opt[onchange]; }
		if($Opt[disabled]){	$aopt[disabled] = $Opt[disabled]; }
		
		if(cForm::ReturnValue($NameY) || cForm::ReturnValue($NameM) || cForm::ReturnValue($NameD)){
			$DefY = cForm::ReturnValue($NameY);
			$DefM = cForm::ReturnValue($NameM);
			$DefD = cForm::ReturnValue($NameD);
		}else{
			list($DefY,$DefM,$DefD) = split("-",$Default);
		}
		
		
		if($confirm){
			if($nodata && !abs($DefY) && !abs($DefM) && !abs($DefD)){
				
			}elseif($Opt[show]){
				print($DefY.$Yopt." ".$DefM.$Mopt." ".$DefD.$Dopt);
			}else{
				print($DefY."/".$DefM."/".$DefD);
			}
			
			cForm::Hidden($NameY, $DefY); 
			cForm::Hidden($NameM, $DefM);
			cForm::Hidden($NameD, $DefD);
			cForm::Hidden($Name, $DefY.'-'.sprintf("%02d",$DefM).'-'.sprintf("%02d",$DefD));
			
		}else{
			//	Year
			cForm::Text(0, $NameY, $DefY, array("size"=>"5","maxlength"=>"4","style"=>"text-align: right; ime-mode: disabled")+$aopt); 
			print($Yopt);
			
			//	Month
			cForm::Text(0, $NameM, $DefM, array("size"=>"3","maxlength"=>"2","style"=>"text-align: right; ime-mode: disabled")+$aopt); 
			print($Mopt);
			
			//	Day
			cForm::Text(0, $NameD, $DefD, array("size"=>"3","maxlength"=>"2","style"=>"text-align: right; ime-mode: disabled")+$aopt); 
			print($Dopt);
			
			//	date;
			cForm::Hidden($Name, $DefY.'-'.sprintf("%02d",$DefM).'-'.sprintf("%02d",$DefD));
		}
	}
	

	////	Date (Y-m)
	function GroupDateYm($confirm="", $Name="", $Default="", $Opt=""){

		
		$aopt = array();	//	オプション配列
		
		//	初期値
		if($Opt[yearmin]){		$YearMin = $Opt[yearmin];		}else{	$YearMin = date("Y");		}
		if($Opt[yearmax]){		$YearMax = $Opt[yearmax];		}else{	$YearMax = date("Y");		}
		if($Opt[nodata]){		$nodata = 1;					}

		if(!$Default){			
			if($nodata){
				$Default = "";
			}else{
				$Default = date("Y-m");
			}
		}

		if($Opt[size]){			$size = $Opt[size];				}
		if($Opt[show] == "jp"){
			$Yopt = "年";
			$Mopt = "月";
		}elseif($Opt[show] == "en"){
			$Yopt = "/";
			$Mopt = "/";
		}
		if($Opt[onchange]){	$aopt[onchange] = $Opt[onchange]; }
		if($Opt[disabled]){	$aopt[disabled] = $Opt[disabled]; }
		
		if(cForm::ReturnValue($Name."Y") || cForm::ReturnValue($Name."M"))
		{
			$DefY = cForm::ReturnValue($Name."Y");
			$DefM = cForm::ReturnValue($Name."M");
		}else{
			list($DefY,$DefM) = split("-",$Default);
		}
		
		
		if($confirm){
			if($nodata && !$DefY && !$DefM){
			
			}elseif($Opt[show]){
				print($DefY.$Yopt." ".$DefM.$Mopt);
			}else{
				print($DefY."/".$DefM);
			}
			
			cForm::Hidden($Name."Y", $DefY); 
			cForm::Hidden($Name."M", $DefM);
			cForm::Hidden($Name, $DefY.'-'.sprintf("%02d",$DefM));
			
		}else{
			//	Year
			cForm::Date(0, $Name."Y", $DefY, array("min"=>$YearMin, "max"=>$YearMax, "show"=>$Yopt, "nodata"=>$nodata, "size"=>$size)+$aopt); 
			
			//	Month
			cForm::Date(0, $Name."M", $DefM, array("min"=>1, "max"=>12, "show"=>$Mopt, "nodata"=>$nodata, "size"=>$size)+$aopt);
			
			//	date;
			cForm::Hidden($Name, $DefY.'-'.sprintf("%02d",$DefM));
		}
	}
	
	function GroupDateYmSet($Name){
		if(cForm::ReturnValue($Name."Y") || cForm::ReturnValue($Name."M")){
			$DefY = cForm::ReturnValue($Name."Y");
			$DefM = cForm::ReturnValue($Name."M");
		}else{
			list($DefY,$DefM) = split("-",cForm::ReturnValue($Name));
		}
		return($DefY . "-" . sprintf("%02d",$DefM));
	}
	
		
	////	Date (Y-m-d h-i)
	function GroupDateTime($confirm="", $Name="", $Default="", $Opt=""){
		
		//	初期値
		if(!$Default){			$Default = date("Y-m-d 00:00");		}
		if($Opt[yearmin]){		$YearMin = $Opt[yearmin];		}else{	$YearMin = date("Y");		}
		if($Opt[yearmax]){		$YearMax = $Opt[yearmax];		}else{	$YearMax = date("Y");		}
		if($Opt[nodata]){		$nodata = 1;					}
		if($Opt[size]){			$size = $Opt[size];				}
		if($Opt[show] == "jp"){
			$Yopt = "年";
			$Mopt = "月";
			$Dopt = "日";
			$Hopt = "時";
			$Iopt = "分";
		}elseif($Opt[show] == "en"){
			$Yopt = "/";
			$Mopt = "/";
			$Dopt = "/";
			$Hopt = "/";
			$Iopt = "/";
		}
		
		//	define
		if(cForm::ReturnValue($Name."Y") || cForm::ReturnValue($Name."M") || cForm::ReturnValue($Name."D") || cForm::ReturnValue($Name."H") || cForm::ReturnValue($Name."I"))
		{
			$DefY = cForm::ReturnValue($Name."Y");
			$DefM = cForm::ReturnValue($Name."M");
			$DefD = cForm::ReturnValue($Name."D");
			$DefH = cForm::ReturnValue($Name."H");
			$DefI = cForm::ReturnValue($Name."I");
			
		}else{
			ereg("([0-9]{4})-([0-9]{1,2})-([0-9]{1,2}) ([0-9]{1,2}):([0-9]{1,2})(.*)", $Default, $Defregs);
			$DefY = $Defregs[1];
			$DefM = $Defregs[2];
			$DefD = $Defregs[3];
			$DefH = $Defregs[4];
			$DefI = $Defregs[5];
		}
		
		if($confirm){
			if($nodata && !$DefY && !$DefM && !$DefD && !$DefH && !$DefI){

			}elseif($Opt[show]){
				print($DefY.$Yopt." ".$DefM.$Mopt." ".$DefD.$Dopt." ".$DefH.$Hopt." ".$DefI.$Iopt);
			}else{
				print($DefY."/".$DefM."/".$DefD." ".$DefH.":".$DefI);
			}
			
			cForm::Hidden($Name."Y", $DefY); 
			cForm::Hidden($Name."M", $DefM);
			cForm::Hidden($Name."D", $DefD);
			cForm::Hidden($Name."H", $DefH);
			cForm::Hidden($Name."I", $DefI);
			
			cForm::Hidden($Name, $DefY."-".$DefM."-".$DefD." ".$DefH.":".$DefI);
		}else{
			//	Year
			cForm::Date($confirm, $Name."Y", $DefY, array("min"=>$YearMin, "max"=>$YearMax, "show"=>$Yopt, "nodata"=>$nodata, "size"=>$size)); 
			
			//	Month
			cForm::Date($confirm, $Name."M", $DefM, array("min"=>1, "max"=>12, "show"=>$Mopt, "nodata"=>$nodata, "size"=>$size));
			
			//	Day
			cForm::Date($confirm, $Name."D", $DefD, array("min"=>1, "max"=>31, "show"=>$Dopt, "nodata"=>$nodata, "size"=>$size));
			
			print("　");
			
			//	Hour
			cForm::Date($confirm, $Name."H", $DefH, array("min"=>0, "max"=>23, "show"=>$Hopt, "nodate"=>$nodate, "size"=>$size));
			
			//	I?
			cForm::Date($confirm, $Name."I", $DefI, array("min"=>0, "max"=>60, "show"=>$Iopt, "nodate"=>$nodate, "size"=>$size));
			
		}
	}

		
	////	Date (Y-m-d h-i)
	function GroupTime($confirm="",$Name="",$Default="",$Opt=""){
		
		//	初期値
		if(!$Default){			$Default = date("00:00");		}
		if($Opt[nodata]){		$nodata = 1;					}
		if($Opt[size]){			$size = $Opt[size];				}
		if($Opt[show] == "jp"){
			$Hopt = "時";
			$Iopt = "分";
		}elseif($Opt[show] == "en"){
			$Hopt = ":";
		}
		
		//	define
		if(cForm::ReturnValue($Name."H") || cForm::ReturnValue($Name."I")){
		
			$DefH = cForm::ReturnValue($Name."H");
			$DefI = cForm::ReturnValue($Name."I");
			
		}else{
			ereg("([0-9]{1,2}):([0-9]{1,2})(.*)", $Default, $Defregs);
			$DefH = $Defregs[1];
			$DefI = $Defregs[2];
		}
		
		if($confirm){
			if($nodata && !$DefH && !$DefI){

			}elseif($Opt[show]){
				print($DefH.$Hopt.sprintf("%02d",$DefI).$Iopt);
			}else{
				print($DefH.":".sprintf("%02d",$DefI));
			}
			
			cForm::Hidden($Name."H", $DefH);
			cForm::Hidden($Name."I", $DefI);
			
			cForm::Hidden($Name, $DefH.":".sprintf("%02d",$DefI).":00");
		}else{
			//	Hour
			cForm::Date($confirm, $Name."H", $DefH, array("min"=>0, "max"=>23, "show"=>$Hopt, "nodate"=>$nodate, "size"=>$size));
			
			//	mInutes?
			cForm::Date($confirm, $Name."I", $DefI, array("min"=>0, "max"=>60, "show"=>$Iopt, "nodate"=>$nodate, "size"=>$size));
			
		}
	}

	

	function GroupDateSet($Name){
		if(strlen(cForm::ReturnValue($Name."Y")) || strlen(cForm::ReturnValue($Name."M")) || strlen(cForm::ReturnValue($Name."D"))){
			$DefY = cForm::ReturnValue($Name."Y");
			$DefM = cForm::ReturnValue($Name."M");
			$DefD = cForm::ReturnValue($Name."D");
		}else{
		//	list($DefY,$DefM,$DefD) = split("-",cForm::ReturnValue($Name));
		}
		return(sprintf("%04d",$DefY) . "-" . sprintf("%02d",$DefM) . "-" . sprintf("%02d",$DefD));
	}



	function GroupDateTimeSet($Name){
		if(cForm::ReturnValue($Name."Y") || cForm::ReturnValue($Name."M") || cForm::ReturnValue($Name."D") || cForm::ReturnValue($Name."H") || cForm::ReturnValue($Name."I"))
		{
			$DefY = cForm::ReturnValue($Name."Y");
			$DefM = cForm::ReturnValue($Name."M");
			$DefD = cForm::ReturnValue($Name."D");
			$DefH = cForm::ReturnValue($Name."H");
			$DefI = cForm::ReturnValue($Name."I");
			
		}else{
			ereg("([0-9]{4})-([0-9]{1,2})-([0-9]{1,2}) ([0-9]{1,2}):([0-9]{1,2})(.*)", cForm::ReturnValue($Name), $Defregs);
			$DefY = $Defregs[1];
			$DefM = $Defregs[2];
			$DefD = $Defregs[3];
			$DefH = $Defregs[4];
			$DefI = $Defregs[5];
		}
		return($DefY . "-" . sprintf("%02d",$DefM) . "-" . sprintf("%02d",$DefD) . " " . sprintf("%02",$DefH) . ":" . sprintf("%02d",$DefI));
	}

	//
	//	画像登録フォーム
	//
	//	[$Opt]
	//		size:			<input type="file" size=...>;
	//		filename:		保存先のファイル名
	//		auto_extension:	保存先のファイル名を指定したときの、拡張子の有無 { Y, N }
	//
	function Image($confirm, $Name, $Default, $MovePath, $DelBtn=0, $Opt=array()){
		
		if($Opt['size']){
			$size = " size='{$Opt['size']}'";
		}
		if(!$Opt['auto_extension']){
			$Opt['auto_extension'] = "Y";
		}
		
		if($confirm){
			if($DelBtn && $_POST[$Name . '_del']){

				//	安全の為、$MovePathとファイルがマッチするかチェック
				if(eregi($MovePath,$_POST[$Name])){
					if(substr($_POST[$Name],0,1) == '/'){
					//	@unlink($_SERVER[DOCUMENT_ROOT] . $_POST[$Name]);
					}else{
					//	@unlink($_POST[$Name]);
					}
				}
				echo "<input type=\"hidden\" name=\"{$Name}\" value=\"\">\n";
			}else{
			
				//	仮登録
				if(is_uploaded_file($_FILES[$Name.'_f'][tmp_name])){
					//echo "<pre>";print_r($Opt);echo "</pre>";
					
					if($Opt['filename'] && $Opt['auto_extension']=="Y"){
						
						if($extype=$_FILES[$Name.'_f']['type']){
							if(ereg("jpeg", $extype)){
								$exten = "jpg";
							}elseif(ereg("gif", $extype)){
								$exten = "gif";
							}elseif(ereg("png", $extype)){
								$exten = "png";
							}elseif(ereg("csv", $extype)){
								$exten = "csv";
							}else{
								$typearr = explode("/", $_FILES[$Name.'_f']['type']);
								$exten = $typearr[(count($typearr)-1)];
							}
						}
						$fn = $Opt['filename'] . "." . $exten;
						
					}elseif($Opt['filename'] && $Opt['auto_extension']=="N"){
						$fn = $Opt['filename'];
					}else{
						$fn = $_FILES[$Name.'_f']['name'];
					}
					
					if((substr($MovePath,-1)) == "/"){
						$src = $MovePath . $fn;
					}elseif($MovePath){
						$src = $MovePath;
					}else{
						$src = "./" . $fn;
					}

					//	ファイル指定がApacheのDocumentRootからの場合書き換え
					if(substr($src,0,1) == '/'){
						$tsrc = $_SERVER[DOCUMENT_ROOT] . $src;
					}else{
						$tsrc = $src;
					}
					
					//	指定のディレクトリに移行
					if(move_uploaded_file($_FILES[$Name.'_f'][tmp_name], $tsrc)){
						echo "<img src=\"{$src}\" border=0>";
						echo "<input type=\"hidden\" name=\"{$Name}\" value=\"{$src}\">\n";
					}
				//	前に仮登録したもの
				}elseif($_POST[$Name]){
					print('<img src="' . $_POST[$Name] . '" border="0">');
					echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $_POST[$Name] . "\">\n";
				}
			}
			
		}else{

			if(substr($Default,0,1) == '/'){
				$PathCheck = $_SERVER[DOCUMENT_ROOT] . $Default;
			}
			
			//	一番始めだけ入れ替え
			if(file_exists($PathCheck) && !$_POST["BefPath_" . $Name]){
				$_POST[$Name] = $Default;
			}
			
			//	現在のファイルを表示
			if($_POST[$Name]){
				echo "<br>";
				echo "<img src=\"" . $_POST[$Name] . "\" border=0><br>\n";
				echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $_POST[$Name] . "\">\n";
			}

			echo "<input type=\"file\" name=\"{$Name}_f\"{$size}>";
			if($DelBtn && $_POST[$Name]){
				print('<input type="checkbox" name="'.$Name.'_del">削除');
			}
		}
		//	ディフォルト用
		echo "<input type=\"hidden\" name=\"BefPath_{$Name}\" value=\"{$Default}\">";
	}


	// 隠しフォーム
	function Hidden($Name="",$Value=""){
		$val = cForm::ReturnValue($Name);
		print('<input type="hidden" name="'.$Name.'" value="'. cForm::SP_ENT($Value) .'">');
		echo "\n";
	}
	
	//	コメント
	function Memo($confirm, $Memo, $Opt=array()){
		
		if($Opt["class"]){
			$Option .= " class=\"" . $Opt["class"] . "\"";
		}
		if($Opt[style]){
			$Option .= " style=\"" . $Opt[style] . "\"";
		}
		if($Opt[id]){
			$Option .= " id=\"" . $Opt[id] . "\"";
		}
		
		if(!$confirm){
			echo "<span{$Option}>" . $Memo . "</span>";
		}
	}
}	
?>
