<?php
/**
 * WordPress 縺ｮ蝓ｺ譛ｬ險ｭ螳・
 *
 * 縺薙・繝輔ぃ繧､繝ｫ縺ｯ縲√う繝ｳ繧ｹ繝医・繝ｫ譎ゅ↓ wp-config.php 菴懈・繧ｦ繧｣繧ｶ繝ｼ繝峨′蛻ｩ逕ｨ縺励∪縺吶・
 * 繧ｦ繧｣繧ｶ繝ｼ繝峨ｒ莉九＆縺壹↓縺薙・繝輔ぃ繧､繝ｫ繧・"wp-config.php" 縺ｨ縺・≧蜷榊燕縺ｧ繧ｳ繝斐・縺励※
 * 逶ｴ謗･邱ｨ髮・＠縺ｦ蛟､繧貞・蜉帙＠縺ｦ繧ゅ°縺ｾ縺・∪縺帙ｓ縲・
 *
 * 縺薙・繝輔ぃ繧､繝ｫ縺ｯ縲∽ｻ･荳九・險ｭ螳壹ｒ蜷ｫ縺ｿ縺ｾ縺吶・
 *
 * * MySQL 險ｭ螳・
 * * 遘伜ｯ・嵯
 * * 繝・・繧ｿ繝吶・繧ｹ繝・・繝悶Ν謗･鬆ｭ霎・
 * * ABSPATH
 *
 * @link http://wpdocs.osdn.jp/wp-config.php_%E3%81%AE%E7%B7%A8%E9%9B%86
 *
 * @package WordPress
 */

// 豕ｨ諢・
// Windows 縺ｮ "繝｡繝｢蟶ｳ" 縺ｧ縺薙・繝輔ぃ繧､繝ｫ繧堤ｷｨ髮・＠縺ｪ縺・〒縺上□縺輔＞ !
// 蝠城｡後↑縺丈ｽｿ縺医ｋ繝・く繧ｹ繝医お繝・ぅ繧ｿ
// (http://wpdocs.osdn.jp/%E7%94%A8%E8%AA%9E%E9%9B%86#.E3.83.86.E3.82.AD.E3.82.B9.E3.83.88.E3.82.A8.E3.83.87.E3.82.A3.E3.82.BF 蜿ら・)
// 繧剃ｽｿ逕ｨ縺励∝ｿ・★ UTF-8 縺ｮ BOM 縺ｪ縺・(UTF-8N) 縺ｧ菫晏ｭ倥＠縺ｦ縺上□縺輔＞縲・

// ** MySQL 險ｭ螳・- 縺薙・諠・ｱ縺ｯ繝帙せ繝・ぅ繝ｳ繧ｰ蜈医°繧牙・謇九＠縺ｦ縺上□縺輔＞縲・** //
/** WordPress 縺ｮ縺溘ａ縺ｮ繝・・繧ｿ繝吶・繧ｹ蜷・*/
define('DB_NAME', 'database_name_here');

/** MySQL 繝・・繧ｿ繝吶・繧ｹ縺ｮ繝ｦ繝ｼ繧ｶ繝ｼ蜷・*/
define('DB_USER', 'username_here');

/** MySQL 繝・・繧ｿ繝吶・繧ｹ縺ｮ繝代せ繝ｯ繝ｼ繝・*/
define('DB_PASSWORD', 'password_here');

/** MySQL 縺ｮ繝帙せ繝亥錐 */
define('DB_HOST', 'localhost');

/** 繝・・繧ｿ繝吶・繧ｹ縺ｮ繝・・繝悶Ν繧剃ｽ懈・縺吶ｋ髫帙・繝・・繧ｿ繝吶・繧ｹ縺ｮ譁・ｭ励そ繝・ヨ */
define('DB_CHARSET', 'utf8');

/** 繝・・繧ｿ繝吶・繧ｹ縺ｮ辣ｧ蜷磯・ｺ・(縺ｻ縺ｨ繧薙←縺ｮ蝣ｴ蜷亥､画峩縺吶ｋ蠢・ｦ√・縺ゅｊ縺ｾ縺帙ｓ) */
define('DB_COLLATE', '');

/**#@+
 * 隱崎ｨｼ逕ｨ繝ｦ繝九・繧ｯ繧ｭ繝ｼ
 *
 * 縺昴ｌ縺槭ｌ繧堤焚縺ｪ繧九Θ繝九・繧ｯ (荳諢・ 縺ｪ譁・ｭ怜・縺ｫ螟画峩縺励※縺上□縺輔＞縲・
 * {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org 縺ｮ遘伜ｯ・嵯繧ｵ繝ｼ繝薙せ} 縺ｧ閾ｪ蜍慕函謌舌☆繧九％縺ｨ繧ゅ〒縺阪∪縺吶・
 * 蠕後〒縺・▽縺ｧ繧ょ､画峩縺励※縲∵里蟄倥・縺吶∋縺ｦ縺ｮ cookie 繧堤┌蜉ｹ縺ｫ縺ｧ縺阪∪縺吶ゅ％繧後↓繧医ｊ縲√☆縺ｹ縺ｦ縺ｮ繝ｦ繝ｼ繧ｶ繝ｼ繧貞ｼｷ蛻ｶ逧・↓蜀阪Ο繧ｰ繧､繝ｳ縺輔○繧九％縺ｨ縺ｫ縺ｪ繧翫∪縺吶・
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         'put your unique phrase here');
define('SECURE_AUTH_KEY',  'put your unique phrase here');
define('LOGGED_IN_KEY',    'put your unique phrase here');
define('NONCE_KEY',        'put your unique phrase here');
define('AUTH_SALT',        'put your unique phrase here');
define('SECURE_AUTH_SALT', 'put your unique phrase here');
define('LOGGED_IN_SALT',   'put your unique phrase here');
define('NONCE_SALT',       'put your unique phrase here');

/**#@-*/

/**
 * WordPress 繝・・繧ｿ繝吶・繧ｹ繝・・繝悶Ν縺ｮ謗･鬆ｭ霎・
 *
 * 縺昴ｌ縺槭ｌ縺ｫ繝ｦ繝九・繧ｯ (荳諢・ 縺ｪ謗･鬆ｭ霎槭ｒ荳弱∴繧九％縺ｨ縺ｧ荳縺､縺ｮ繝・・繧ｿ繝吶・繧ｹ縺ｫ隍・焚縺ｮ WordPress 繧・
 * 繧､繝ｳ繧ｹ繝医・繝ｫ縺吶ｋ縺薙→縺後〒縺阪∪縺吶ょ濠隗定恭謨ｰ蟄励→荳狗ｷ壹・縺ｿ繧剃ｽｿ逕ｨ縺励※縺上□縺輔＞縲・
 */
$table_prefix  = 'wp_';

/**
 * 髢狗匱閠・∈: WordPress 繝・ヰ繝・げ繝｢繝ｼ繝・
 *
 * 縺薙・蛟､繧・true 縺ｫ縺吶ｋ縺ｨ縲・幕逋ｺ荳ｭ縺ｫ豕ｨ諢・(notice) 繧定｡ｨ遉ｺ縺励∪縺吶・
 * 繝・・繝槭♀繧医・繝励Λ繧ｰ繧､繝ｳ縺ｮ髢狗匱閠・↓縺ｯ縲√◎縺ｮ髢狗匱迺ｰ蠅・↓縺翫＞縺ｦ縺薙・ WP_DEBUG 繧剃ｽｿ逕ｨ縺吶ｋ縺薙→繧貞ｼｷ縺乗耳螂ｨ縺励∪縺吶・
 *
 * 縺昴・莉悶・繝・ヰ繝・げ縺ｫ蛻ｩ逕ｨ縺ｧ縺阪ｋ螳壽焚縺ｫ縺､縺・※縺ｯ Codex 繧偵＃隕ｧ縺上□縺輔＞縲・
 *
 * @link http://wpdocs.osdn.jp/WordPress%E3%81%A7%E3%81%AE%E3%83%87%E3%83%90%E3%83%83%E3%82%B0
 */
define('WP_DEBUG', false);

/* 邱ｨ髮・′蠢・ｦ√↑縺ｮ縺ｯ縺薙％縺ｾ縺ｧ縺ｧ縺・! WordPress 縺ｧ繝悶Ο繧ｰ繧偵♀讌ｽ縺励∩縺上□縺輔＞縲・*/

/** Absolute path to the WordPress directory. */
if ( !defined('ABSPATH') )
	define('ABSPATH', dirname(__FILE__) . '/');

/** Sets up WordPress vars and included files. */
require_once(ABSPATH . 'wp-settings.php');
