<?
require_once("/var/common/class/ExcelParserPro/excelparser.php");

class ExcelParser extends ExcelFileParser{


function getSheetArray(&$ws){

	//	checking row & column
	if(!$ws['max_row']){ return false; }
	if(!$ws['max_col']){ return false; }

    for($i=0;$i<=$ws['max_row'];$i++){

        //  getting one row data
        for( $j=0; $j<=$ws['max_col']; $j++ ) {

            unset($value);
            if(isset($ws['cell'][$i][$j])){

                //  copy cell object
                $data = $ws['cell'][$i][$j];


                if($data['type']==0){
                    if($this->sst['unicode'][$data['data']]){
                        // string
                        $value = mb_convert_encoding($this->sst['data'][$data['data']],"EUC","UCS-2LE");
			//			print("excel2k:".$i.$j.":".$value."\n");
                    }else{
                        // ascii
                       // $value = $this->sst['data'][$data['data']];
                        $value = mb_convert_encoding($this->sst['data'][$data['data']],"EUC","SJIS");
			//			print("excel5:".$i.$j.":".$value."\n");
                    }
                }else{
                    // numeric & date
                    $value = $data['data'];
			//		print("num?:".$i.$j.":".$value."\n");
                }
            }else{
		//		print("unset:".$i.$j.":".$value."\n");
			}
            $ret[$i][$j] = $value;
        }
	}
	return $ret;

}


}
?>
