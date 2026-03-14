<?php
class TypeSquare_Admin_Root extends TypeSquare_Admin_Base {
	private static $instance;
	private static $text_domain;
	private function __construct(){}

	public static function get_instance() {
		if ( ! isset( self::$instance ) ) {
			$c = __CLASS__;
			self::$instance = new $c();
		}
		return self::$instance;
	}

	public function typesquare_post_metabox() {
		$fonts = TypeSquare_ST_Fonts::get_instance();
		$param = $fonts->get_fonttheme_params();
		if ( 'false' == $param['typesquare_themes']['show_post_form'] || ! $param['typesquare_themes']['show_post_form'] ) {
			return;
		}
		$post_type = array( 'post', 'page' );
		foreach ( $post_type as $type ) {
			add_meta_box( 'typesquare_post_metabox', __( 'TypeSquare Webfonts for SAKURA RS', self::$text_domain ), array( $this, 'typesquare_post_metabox_inside' ), $type, 'advanced', 'low' );
		}
	}

	public function typesquare_post_metabox_inside() {
		$html  = '';
		$html .= '<p>'. __( '縺薙・險倅ｺ九↓驕ｩ逕ｨ縺吶ｋ繝輔か繝ｳ繝医ｒ驕ｸ謚槭＠縺ｦ縺上□縺輔＞', self::$text_domain ) . '</p>';

		$html .= $this->_get_post_font_theme_selector();
		$html .= '<input type="hidden" name="typesquare_nonce_postmeta" id="typesquare_nonce_postmeta" value="' . wp_create_nonce( plugin_basename( __FILE__ ) ) . '" />';
		echo $html;
	}

	private function _get_post_font_theme_selector() {
		$html  = '';
		$fonts = TypeSquare_ST_Fonts::get_instance();
		$all_font_theme = $fonts->load_all_font_data( );
		$selected_theme = $fonts->get_selected_post_fonttheme( get_the_ID() );
		$option  = '';
		$option .= "<option value='false'>繝・・繝槭ｒ險ｭ螳壹＠縺ｪ縺・/option>";
		foreach ( $all_font_theme as $key => $fonttheme ) {
			$fonttheme_name = $this->get_fonts_text( $fonttheme['name'] );
			$font_text = $this->_get_fonttheme_text( $fonttheme );
			$selected = '';
			if ( $key === $selected_theme ) {
				$selected = 'selected';
			}
			$option .= "<option value='{$key}' {$selected}>";
			$option .= "{$fonttheme_name} ( {$font_text} )";
			$option .= '</option>';
		}
		$html .= '<h3>'. __( '繝輔か繝ｳ繝医ユ繝ｼ繝槭°繧蛾∈縺ｶ', self::$text_domain ) . '</h3>';
		$html .= "<select name='typesquare_fonttheme[theme]'>{$option}</select>";
		return $html;
	}

	public function typesquare_save_post( $post_id ) {
		if ( ! isset( $_POST['typesquare_nonce_postmeta'] ) ) {
			return;
		}
		//Verify
		if ( ! wp_verify_nonce( $_POST['typesquare_nonce_postmeta'], plugin_basename( __FILE__ ) ) ) {
			return $post_id;
		}
		// if auto save
		if ( defined( 'DOING_AUTOSAVE' ) && DOING_AUTOSAVE ) {
			return $post_id;
		}

		// permission check
		if ( 'page' == $_POST['post_type'] ) {
			if ( ! current_user_can( 'edit_page', $post_id ) ) {
				return $post_id;
			}
		} else {
			if ( ! current_user_can( 'edit_post', $post_id ) ) {
				return $post_id;
			}
		}

		// save action
		$fonttheme = $_POST['typesquare_fonttheme'];
		$current_option = get_post_meta( $post_id, 'typesquare_fonttheme' );
		$fonts = TypeSquare_ST_Fonts::get_instance();
		if ( isset( $current_option[0] ) ) {
			$current = $current_option[0];
		} else {
			$current = $fonttheme;
		}
		$font['theme'] = esc_attr( $fonttheme['theme'] );
		update_post_meta( $post_id, 'typesquare_fonttheme', $font );
		return $post_id;
	}

	private function get_fonts_text( $fonts ) {
		if ( is_array( $fonts ) ) {
			$text_font = '';
			foreach ( $fonts as $key => $font ) {
				$text_font .= esc_attr( $font );
				if ( count( $fonts ) - 1 > $key  ) {
					$text_font .= ' + ';
				}
			}
		} else {
			$text_font    = esc_attr( $fonts );
		}
		return $text_font;
	}

	public function typesquare_admin_menu() {
		$param = $this->get_auth_params();
		$option_name = 'typesquare_auth';
		$nonce_key = TypeSquare_ST::OPTION_NAME;
		echo "<div class='wrap'>";
		echo '<h2>'. __( 'TypeSquare Webfonts Plugin for 縺輔￥繧峨・繝ｬ繝ｳ繧ｿ繝ｫ繧ｵ繝ｼ繝・ , self::$text_domain ). '</h2>';
		do_action( 'typesquare_add_setting_before' );
		$autho_param = $this->get_auth_params();
		if ( false !== $autho_param['typesquare_auth']['auth_status'] ) {
			echo $this->get_font_theme_form();
			echo '<hr/>';
			echo "<div class='ts-custome_form_row'>";
			echo '<span><h3 class="toggleText toggleAdvanced mTop20">'. __( '荳顔ｴ夊・髄縺代・繧ｫ繧ｹ繧ｿ繝槭う繧ｺ', self::$text_domain ). '<span class="advancedTriangle">笆ｼ</span></h3></span>';
			echo "<div class='ts-custome_form hidden'>";
			echo $this->get_font_target_form();
			echo $this->update_font_list_form();
			echo $this->_get_post_font_form();
			echo '</div>';
			echo '</div>';
		}
		do_action( 'typesquare_add_setting_after' );
	}

	private function _get_post_font_form() {
		$option_name = 'typesquare_fonttheme';
		$fonts = TypeSquare_ST_Fonts::get_instance();
		$param = $fonts->get_fonttheme_params();
		$keys = $param['typesquare_themes_keys'];
		$html  = '';
		$html .= '<hr/>';
		$html .= "<form method='post' action=''>";
		$html .= '<h3>'. __( '蛟句挨險倅ｺ九ヵ繧ｩ繝ｳ繝郁ｨｭ螳・ , self::$text_domain ). '</h3>';
		$html .= '<p>'. __( '蛟句挨險倅ｺ倶ｽ懈・逕ｻ髱｢縺ｫ繝輔か繝ｳ繝郁ｨｭ螳壹ｒ陦ｨ遉ｺ縺励∪縺吶・ , self::$text_domain ). '</p>';
		$html .= wp_nonce_field( 'ts_update_font_settings' , 'ts_update_font_settings' , true , false );
		$html .= "<table class='widefat form-table'>";
		$html .= '<tbody>';
		$html .= "<tr><th>縲{$keys['show_post_form']}</th><td>";
		$value = esc_attr( $param['typesquare_themes']['show_post_form'] );
		$html .= '<label>';
		$html .= "<input name='{$option_name}[show_post_form]' type='hidden' id='show_post_form' value='false' class='code'/>";
		$html .= "<input name='{$option_name}[show_post_form]' value='true' id='show_post_form' type='checkbox' class='code' ".checked( $value, 'true', true )."/>";
		$html .= __( '譛牙柑蛹悶☆繧・ , self::$text_domain );
		$html .= '</label>';
		$html .= '<p>'. __( '繝・ヵ繧ｩ繝ｫ繝医〒縺ｯ繝輔か繝ｳ繝医ユ繝ｼ繝櫁ｨｭ螳壹′辟｡蜉ｹ蛹悶＆繧後※縺・∪縺吶・ , self::$text_domain ). '</p>';
		$html .= '</td></tr>';
		$html .= '<tr><th></th><td style="position: relative; left: -208px;">' . get_submit_button( __( '蛟句挨險倅ｺ九ヵ繧ｩ繝ｳ繝郁ｨｭ螳壹ｒ譖ｴ譁ｰ縺吶ｋ', self::$text_domain ) ) . '</td></tr>';
		$html .= '</tbody>';
		$html .= '</table>';
		$html .= '</form>';
		return $html;

	}

	public function get_font_theme_form() {
		$current = get_option('typesquare_fonttheme');
		$options = get_option( 'typesquare_custom_theme' );
		$edit_theme = false;
		$display = 'display:none';
		if ( isset( $_POST['typesquare_fonttheme'] ) ) {
			$edit_theme = esc_attr( $_POST['typesquare_fonttheme']['font_theme'] );
			$display = "";
		}
		$edit_theme = '';
		if( isset($_POST['ts_change_edit_theme']) ){
			$edit_theme = 'change';
		}
		$edit_mode = '';
		if( isset( $_POST['ts_edit_mode'] ) ) {
			$edit_mode = $_POST['ts_edit_mode'];
		}
		if($edit_theme === 'change'){$display = 'display:none';}
		if($edit_mode === 'delete' || $edit_mode === 'new' || $edit_theme === 'false' || !$edit_theme || !$edit_theme){ $display = 'display:none'; }
		else{$display = "";}
		$option_name = 'typesquare_fonttheme';
		$fonts = TypeSquare_ST_Fonts::get_instance();
		$param = $fonts->get_fonttheme_params();
		$all_font_theme = $fonts->load_all_font_data( );
		$font_theme = TypeSquare_ST_Fonttheme::get_instance();
		$custom_theme_json = $font_theme->get_custom_theme_json();
		if ( $current['font_theme'] && $options['theme'][ $current['font_theme'] ] && $edit_mode !== 'new' ) { $display = ""; }
		if( isset($_POST['typesquare_fonttheme']['font_theme']) &&  $_POST['typesquare_fonttheme']['font_theme'] !== 'new'){
			$param['typesquare_themes']['font_theme'] = $_POST['typesquare_fonttheme']['font_theme'];
		}
		$html  = '';
		$html .= '<hr/>';
		$html .= "<form method='post' action='' id='custmeFontForm'>";
		$html .= '<h3>'. __( '繝輔か繝ｳ繝医ユ繝ｼ繝櫁ｨｭ螳・ , self::$text_domain ). '</h3>';
		$html .= '<p>'. __( '繝輔か繝ｳ繝医ユ繝ｼ繝槭ｒ驕ｸ謚槭＠縺ｦ縺上□縺輔＞縲・ , self::$text_domain ). '<br/>';
		$html .= '<strong>'. __( '窶ｻ縲梧眠縺励￥繝・・繝槭ｒ菴懈・縺吶ｋ縲阪°繧峨∬・逕ｱ縺ｫ繝輔か繝ｳ繝医ユ繝ｼ繝槭ｒ菴懈・縺ｧ縺阪∪縺吶・ , self::$text_domain ). '</strong></p>';
		$html .= wp_nonce_field( 'ts_update_font_settings' , 'ts_update_font_settings' , true , false );
		$html .= "<table class='widefat form-table'>";
		$html .= '<thead>';
		$html .= "<tr><th>縲{$param['typesquare_themes_keys']['font_theme']}</th></tr>";
		$html .= '</thead>';
		$html .= '<tbody>';
		$html .= '<tr><td>';
		$html .= "<select id='fontThemeSelect' name='{$option_name}[font_theme]'>";
		$html .= "<option value='false'>繝・・繝槭ｒ險ｭ螳壹＠縺ｪ縺・/option>";
		$newSelect = '';
		if($edit_mode === 'new'){
			$newSelect = 'selected';
		}
		$html .= "<option value='new' {$newSelect}>譁ｰ縺励￥繝・・繝槭ｒ菴懈・縺吶ｋ</option>";
		foreach ( $all_font_theme as $fonttheme_key => $fonttheme ) {
			$fonttheme_name = esc_attr( $fonttheme['name'] );
			$font_text = $this->_get_fonttheme_text( $fonttheme );
			$selected	= '';
			if ( $fonttheme_key == $param['typesquare_themes']['font_theme'] && $fonttheme_key !== 'false' && !$newSelect ) {
				$selected = 'selected';
			}
			$html .= "<option value='{$fonttheme_key}' {$selected}>";
			$html .= "{$fonttheme_name} ( {$font_text} )";
			$html .= '</option>';
		}
		$html .= '</select>';
		$html .= $this->_get_custome_font_theme_list_form();
		$html .= "<table>";
		$html .= "<th>";
		$html .= get_submit_button( __( '繝輔か繝ｳ繝医ユ繝ｼ繝槭ｒ譖ｴ譁ｰ縺吶ｋ', self::$text_domain ), 'primary', 'fontThemeUpdateButton');
		$html .= "</th>";
		$html .= "<th>";
		$style = array("style"=>"margin-top:15px;".$display);
		$html .= get_submit_button( __( '繝輔か繝ｳ繝医ユ繝ｼ繝槭ｒ蜑企勁縺吶ｋ', self::$text_domain ), 'delete', 'fontThemeDeleteButton', null, $style);
		$html .= "</th>";
		$html .= "</table>";
		$html .= '<input type="hidden" name="typesquare_nonce_postmeta" id="typesquare_nonce_postmeta" value="' . wp_create_nonce( plugin_basename( __FILE__ ) ) . '" />';
		$html .= '</td></tr>';
		$html .= '</tbody>';
		$html .= '</table>';
		$html .= '</form>';
		return $html;
	}

	public function _get_custome_font_theme_list_form() {
		$options = get_option( 'typesquare_custom_theme' );
		$current = get_option('typesquare_fonttheme');
		$edit_theme = false;
		$hidden = ' hidden';
		$require = '';
		if ( isset( $_POST['typesquare_fonttheme'] ) && isset( $_POST['ts_change_edit_theme'] ) ) {
			$edit_theme = esc_attr( $_POST['typesquare_fonttheme']['font_theme'] );
			$hidden = ' hidden';
		}else if($current['font_theme'] && $current['font_theme'] !== 'false'){
			$edit_theme = $current['font_theme'];
		}
		$fonts = TypeSquare_ST_Fonts::get_instance();
		/* @TODO Debug Code
			$option_name = 'typesquare_fonttheme';
			$param = get_option( $option_name );
			unset($param['fonts']);
			update_option( $option_name, $param );
			$param = $fonts->get_fonttheme_options();
			*/
		$edit_mode = '';
		if( isset( $_POST['ts_edit_mode'] ) ) {
			$edit_mode = $_POST['ts_edit_mode'];
		}
		$font_list = $theme_id = $theme_name = '';
		if ( $edit_theme && $options['theme'][ $edit_theme ] ) {
			$theme_name = $options['theme'][ $edit_theme ]['name'];
			$theme_id = $options['theme'][ $edit_theme ]['id'];
			$font_list = $options['fonts'][ $edit_theme ];
			$hidden = ' ';
			$edit_mode = 'update';
		}
		$html  = '';
		if ( $theme_id ) {
			$theme_input = "<input type='hidden'縲id='ts_custome_theme_id' name='typesquare_custom_theme[id]' value='{$theme_id}' />";
			$html .= "<input type='hidden' name='ts_edit_mode' value='update' />";
			$html .= $theme_input;
		} else {
			$theme_id = uniqid();
			$theme_input = false;
			$html .= "<input type='hidden' name='ts_edit_mode' value='update' />";
			if(!$edit_theme || !$edit_mode || $edit_theme === 'false' || $edit_mode === 'delete' || $edit_mode === 'update'){
				$theme_id = '';
			}
			if($theme_id !== ''){
				$html .= "<input type='hidden' id='ts_custome_theme_id' name='typesquare_custom_theme[id]' value='{$theme_id}' maxlength='16' style='width:100%;' pattern='^[0-9A-Za-z]+$' required/>";
			}else {
				$html .= '<input type="hidden" name="ts_custome_theme_id" id="typesquare_custom_theme[id]" value="' . wp_create_nonce( plugin_basename( __FILE__ ) ) . '" />';
			}
		}
		if($edit_mode === 'new'){
			$hidden = ' ';
		}
		if($edit_theme === 'new'){
			$hidden = ' ';
		}
		if(!$edit_theme || !$edit_mode || $edit_theme === 'false' || $edit_mode === 'delete'){
			$hidden = ' hidden';
		}
		if($hidden === ' '){
			$require = 'required';
		}
		$html .= '<hr/>';
		$html .= "<div id='customeFontThemeForm'{$hidden}>";
		$html .= wp_nonce_field( 'ts_update_font_name_setting', 'ts_update_font_name_setting', true , false );
		$html .= "<table class='widefat' style='border: 0px'>";
		$html .= '<tbody>';
		$html .= "<tr><th width='20%''>繝・・繝槭ち繧､繝医Ν</th><td>";
		$html .= "<input type='hidden' id='current_custome_font_name' value='{$theme_name}'/>";
		$html .= "<input type='text' id='custome_font_name' name='typesquare_custom_theme[name]' value='{$theme_name}' maxlength='16' style='width:30%;' {$require}/>";
		$html .= '</td></tr>';
		$html .= '</tbody>';
		$html .= '</table>';
		$html .= "<div id='ts-react-search-font'></div>";
		$html .= "</div>";
		$html .= $this->_get_script( $font_list );
		return $html;
	}

	private function _get_script( $font_list ) {
		$vars  = "var form_id = '#". self::MENU_FONTTHEME. "';";
		$vars .= "var notify_text = '". __( '繝輔か繝ｳ繝医ｒ・醍ｨｮ鬘樔ｻ･荳企∈謚槭＠縺ｦ縺上□縺輔＞縲・, self::$text_domain ). "';";
		$vars .= "var unique_id ='". uniqid() ."';";
		$options = get_option('typesquare_custom_theme');
		$vars .= "var option_font_list = ". json_encode( $options ) .";";
		$vars .= "var plugin_base = '".wp_create_nonce( plugin_basename( __FILE__ ) )."';";
		$fonts = TypeSquare_ST_Fonts::get_instance();
		$all_font_theme = $fonts->load_all_font_data( );
		$vars .= 'var all_font_list = '. json_encode( $all_font_theme ) .';';
$script = <<<EOM
{$vars}
jQuery( document ).ready(function() {
	jQuery( form_id ).submit(function() {
		var title = jQuery( 'select[name="typesquare_custom_theme[fonts][title][font]"]' ).val();
		var lead = jQuery( 'select[name="typesquare_custom_theme[fonts][lead][font]"]' ).val();
		var text = jQuery( 'select[name="typesquare_custom_theme[fonts][text][font]"]' ).val();
		var bold = jQuery( 'select[name="typesquare_custom_theme[fonts][bold][font]"]' ).val();
		if (
			title === 'false' &&
			lead === 'false' &&
			text === 'false' &&
			bold === 'false'
		) {
			alert( notify_text );
			return false;
		}
	});
});
EOM;
		$html = '<script>';
		$endpoint = path_join( TS_PLUGIN_URL , 'inc/font.json' );
		$html .= "var json_endpoint = '{$endpoint}';";
		if ( $font_list ) {
			$html .= "var current_font = ". json_encode( $font_list ) .';';
		} else {
			$html .= "var current_font = false;";
		}
		$html .= $script;
		$html .= '</script>';
		return $html;
	}

	private function _get_fonttheme_text( $fonttheme ) {
		$font_text = '';
		if ( isset( $fonttheme['fonts']['title'] ) ) {
			$font_text .= __( '隕句・縺暦ｼ・, self::$text_domain );
			$font_text .= $this->get_fonts_text( $fonttheme['fonts']['title'] );
			$font_text .= ',';
		}
		if ( isset( $fonttheme['fonts']['lead'] ) ) {
			$font_text .= __( '繝ｪ繝ｼ繝会ｼ・, self::$text_domain );
			$font_text .= $this->get_fonts_text( $fonttheme['fonts']['lead'] );
			$font_text .= ',';
		}
		if ( isset( $fonttheme['fonts']['content'] ) ) {
			$font_text .= __( '譛ｬ譁・ｼ・, self::$text_domain );
			$font_text .= $this->get_fonts_text( $fonttheme['fonts']['content'] );
			$font_text .= ',';
		}
		if ( isset( $fonttheme['fonts']['text'] ) ) {
			$font_text .= __( '譛ｬ譁・ｼ・, self::$text_domain );
			$font_text .= $this->get_fonts_text( $fonttheme['fonts']['text'] );
			$font_text .= ',';
		}
		if ( isset( $fonttheme['fonts']['bold'] ) ) {
			$font_text .= __( '螟ｪ蟄暦ｼ・, self::$text_domain );
			$font_text .= $this->get_fonts_text( $fonttheme['fonts']['bold'] );
		}
		$font_text = rtrim( $font_text, ',' );
		$font_text = str_replace( ",", " / ", $font_text );
		return $font_text;
	}

	public function get_font_target_form() {
		$fonts = TypeSquare_ST_Fonts::get_instance();
		$param = $fonts->get_fonttheme_params();
		$html  = '';
		$html .= "<form method='post' action=''>";
		$html .= '<h3>'. __( '繝輔か繝ｳ繝郁ｨｭ螳壹け繝ｩ繧ｹ' , self::$text_domain ). '</h3>';
		$html .= '<p>'. __( '繝輔か繝ｳ繝医ｒ驕ｩ逕ｨ縺吶ｋ繧ｯ繝ｩ繧ｹ繧呈欠螳壹＠縺ｾ縺吶・ , self::$text_domain ). '</p>';
		$html .= "<table class='widefat form-table'>";
		$html .= '<thead>';
		$key = $param['typesquare_themes_keys'];
		$html .= "<tr><th>縲{$key['title_target']}</th><th>縲{$key['lead_target']}</th><th>縲{$key['text_target']}</th><th>縲{$key['bold_target']}</th></tr>";
		$html .= '</thead>';
		$html .= '<tbody>';
		$data = $param['typesquare_themes'];
		$html .= "<tr><td><input type='text' name='typesquare_fonttheme[title_target]' value='{$data['title_target']}' required/></td>";
		$html .= "<td><input type='text' name='typesquare_fonttheme[lead_target]' value='{$data['lead_target']}' required/></td>";
		$html .= "<td><input type='text' name='typesquare_fonttheme[text_target]' value='{$data['text_target']}' required/></td>";
		$html .= "<td><input type='text' name='typesquare_fonttheme[bold_target]' value='{$data['bold_target']}' required/></td></tr>";
		$html .= "<tr><td>";
		$html .= get_submit_button( __( '險ｭ螳壹け繝ｩ繧ｹ繧呈峩譁ｰ縺吶ｋ', self::$text_domain ) );
		$html .= "</td></tr>";
		$html .= '</tbody>';
		$html .= '</table>';
		$html .= wp_nonce_field( 'ts_update_font_settings' , 'ts_update_font_settings' , true , false );
		$html .= '</form>';
		return $html;
	}

	public function update_font_list_form() {
		$fonts = TypeSquare_ST_Fonts::get_instance();
		$auth_param = $this->get_auth_params();
		if ( false == $auth_param['typesquare_auth']['api_status'] ) {
			return;
		}
		$font_file_path = path_join( TS_PLUGIN_PATH , 'inc/font.json' );
		$param = date("y/m/d", filemtime($font_file_path));
		$html  = '';
		$html .= "<form method='post' action=''>";
		$html .= '<h3>'. __( '繝輔か繝ｳ繝井ｸ隕ｧ縺ｮ譖ｴ譁ｰ' , self::$text_domain ). '</h3>';
		$html .= '<p>'. __( '蛻ｩ逕ｨ蜿ｯ閭ｽ繝輔か繝ｳ繝医・荳隕ｧ繧呈怙譁ｰ迚医↓譖ｴ譁ｰ縺励∪縺吶・ , self::$text_domain ). '</p>';
		$html .= "<table class='widefat form-table'>";
		$html .= '<thead>';
		$html .= "<tr></tr>";
		$html .= '</thead>';
		$html .= "<tbody>";
		$html .= "<tr><td style='width: 1%;'>".get_submit_button( __( '繝輔か繝ｳ繝井ｸ隕ｧ繧呈峩譁ｰ縺吶ｋ', self::$text_domain ) )."</td>";
		$html .= "<td>譛邨よ峩譁ｰ譌･: ".$param."</td></tr>";
		$html .= '</tbody>';
		$html .= '</table>';
		$html .= wp_nonce_field( 'ts_update_font_list' , 'ts_update_font_list' , true , false );
		$html .= '</form>';
		return $html;
	}

}
