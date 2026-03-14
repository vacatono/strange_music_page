<?php

class TypeSquare_ST_Fonttheme {
	private static $fonttheme;
	private static $instance;

	private function __construct(){}

	public static function get_instance() {
		if ( ! isset( self::$instance ) ) {
			$c = __CLASS__;
			self::$instance = new $c();
		}
		return self::$instance;
	}

	public static function get_fonttheme() {
		static $fonttheme;

		$fonttheme = array(
			'basic' => array(
				'name'	=> '繝吶・繧ｷ繝・け',
				'fonts' => array(
					'title'   => '隕句・繧ｴMB31',
					'lead'    => '繧ｫ繧ｯ繝溘Φ R',
					'content' => '譁ｰ繧ｴ R',
					'bold'    => '譁ｰ繧ｴ M',
				),
			),
			'news' => array(
				'name'	=> '繝九Η繝ｼ繧ｹ',
				'fonts' => array(
					'title'   => '繧ｴ繧ｷ繝・けMB101 B',
					'lead'    => '繧ｫ繧ｯ繝溘Φ R',
					'content' => 'UD譁ｰ繧ｴ R',
					'bold'    => 'UD譁ｰ繧ｴ M',
				),
			),
			'fashion' => array(
				'name'	=> '繝輔ぃ繝・す繝ｧ繝ｳ',
				'fonts' => array(
					'title'   => '隗｣繝溘Φ 螳・B',
					'lead'    => '荳ｸ繝輔か繝ｼ繧ｯ M',
					'content' => '繝輔か繝ｼ繧ｯ R',
					'bold'    => '繝輔か繝ｼ繧ｯ M',
				),
			),
			'pop' => array(
				'name'	=> '繝昴ャ繝・,
				'fonts' => array(
					'title'   => '譁ｰ荳ｸ繧ｴ 螟ｪ繝ｩ繧､繝ｳ',
					'lead'    => '縺ｯ繧九・蟄ｦ蝨・,
					'content' => '縺倥ｅ繧・201',
					'bold'    => '縺倥ｅ繧・501',
				),
			),
			'japan_style' => array(
				'name'	=> '蜥碁｢ｨ',
				'fonts' => array(
					'title'   => '髫ｷ譖ｸ101',
					'lead'    => '豁｣讌ｷ譖ｸCB1',
					'content' => '繝ｪ繝･繧ｦ繝溘Φ R-KL',
					'bold'    => '繝ｪ繝･繧ｦ繝溘Φ M-KL',
				),
			),
			'modern' => array(
				'name'	=> '繝｢繝繝ｳ',
				'fonts' => array(
					'title'   => '縺吶★繧縺・,
					'lead'    => '繝医・繧ｭ繝ｳ繧ｰ',
					'content' => '繝翫え-GM',
					'bold'    => '繝翫え-GM',
				),
			),
			'novels' => array(
				'name'	=> '蟆剰ｪｬ',
				'fonts' => array(
					'title'   => '隕句・繝溘ΦMA31',
					'lead'    => '隗｣繝溘Φ 螳・B',
					'content' => 'A1譏取悃',
					'bold'    => 'A1譏取悃',
				),
			),
			'smartphone' => array(
				'name'	=> '繧ｹ繝槭・',
				'fonts' => array(
					'title'   => 'UD譁ｰ繧ｴ M',
					'lead'    => '譁ｰ荳ｸ繧ｴ R',
					'content' => 'UD譁ｰ繧ｴ 繧ｳ繝ｳ繝・Φ繧ｹ90 L',
					'bold'    => 'UD譁ｰ繧ｴ 繧ｳ繝ｳ繝・Φ繧ｹ90 M',
				),
			),
		);

		$options = get_option( 'typesquare_custom_theme' );
		if ( $options && isset( $options['theme'] ) && is_array( $options['theme'] ) ) {
			$fonttheme = $fonttheme + $options['theme'];
		}
		return $fonttheme;
	}

	public static function get_custom_theme_json() {
		$options = get_option( 'typesquare_custom_theme' );
		return json_encode($options['theme']);
	}
}
