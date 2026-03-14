<?php
/**
 * The base configurations of the WordPress.
 *
 * 縺薙・繝輔ぃ繧､繝ｫ縺ｯ縲｀ySQL縲√ユ繝ｼ繝悶Ν謗･鬆ｭ霎槭∫ｧ伜ｯ・嵯縲∬ｨ隱槭、BSPATH 縺ｮ險ｭ螳壹ｒ蜷ｫ縺ｿ縺ｾ縺吶・ * 繧医ｊ隧ｳ縺励＞諠・ｱ縺ｯ {@link http://wpdocs.sourceforge.jp/wp-config.php_%E3%81%AE%E7%B7%A8%E9%9B%86 
 * wp-config.php 縺ｮ邱ｨ髮・ 繧貞盾辣ｧ縺励※縺上□縺輔＞縲・ySQL 縺ｮ險ｭ螳壽ュ蝣ｱ縺ｯ繝帙せ繝・ぅ繝ｳ繧ｰ蜈医ｈ繧雁・謇九〒縺阪∪縺吶・ *
 * 縺薙・繝輔ぃ繧､繝ｫ縺ｯ繧､繝ｳ繧ｹ繝医・繝ｫ譎ゅ↓ wp-config.php 菴懈・繧ｦ繧｣繧ｶ繝ｼ繝峨′蛻ｩ逕ｨ縺励∪縺吶・ * 繧ｦ繧｣繧ｶ繝ｼ繝峨ｒ莉九＆縺壹√％縺ｮ繝輔ぃ繧､繝ｫ繧・"wp-config.php" 縺ｨ縺・≧蜷榊燕縺ｧ繧ｳ繝斐・縺励※逶ｴ謗･邱ｨ髮・＠蛟､繧・ * 蜈･蜉帙＠縺ｦ繧ゅ°縺ｾ縺・∪縺帙ｓ縲・ *
 * @package WordPress
 */

// 豕ｨ諢・ 
// Windows 縺ｮ "繝｡繝｢蟶ｳ" 縺ｧ縺薙・繝輔ぃ繧､繝ｫ繧堤ｷｨ髮・＠縺ｪ縺・〒縺上□縺輔＞ !
// 蝠城｡後↑縺丈ｽｿ縺医ｋ繝・く繧ｹ繝医お繝・ぅ繧ｿ
// (http://wpdocs.sourceforge.jp/Codex:%E8%AB%87%E8%A9%B1%E5%AE%A4 蜿ら・)
// 繧剃ｽｿ逕ｨ縺励∝ｿ・★ UTF-8 縺ｮ BOM 縺ｪ縺・(UTF-8N) 縺ｧ菫晏ｭ倥＠縺ｦ縺上□縺輔＞縲・
// ** MySQL 險ｭ螳・- 縺薙■繧峨・諠・ｱ縺ｯ繝帙せ繝・ぅ繝ｳ繧ｰ蜈医°繧牙・謇九＠縺ｦ縺上□縺輔＞縲・** //
/** WordPress 縺ｮ縺溘ａ縺ｮ繝・・繧ｿ繝吶・繧ｹ蜷・*/
define('DB_NAME', 'vacatono_wp');

/** MySQL 繝・・繧ｿ繝吶・繧ｹ縺ｮ繝ｦ繝ｼ繧ｶ繝ｼ蜷・*/
define('DB_USER', 'vacatono');

/** MySQL 繝・・繧ｿ繝吶・繧ｹ縺ｮ繝代せ繝ｯ繝ｼ繝・*/
define('DB_PASSWORD', '00mole00');

/** MySQL 縺ｮ繝帙せ繝亥錐 */
define('DB_HOST', 'mysql708.db.sakura.ne.jp');

/** 繝・・繧ｿ繝吶・繧ｹ縺ｮ繝・・繝悶Ν繧剃ｽ懈・縺吶ｋ髫帙・繝・・繧ｿ繝吶・繧ｹ縺ｮ繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ繧ｻ繝・ヨ */
define('DB_CHARSET', 'utf8');

/** 繝・・繧ｿ繝吶・繧ｹ縺ｮ辣ｧ蜷磯・ｺ・(縺ｻ縺ｨ繧薙←縺ｮ蝣ｴ蜷亥､画峩縺吶ｋ蠢・ｦ√・縺ゅｊ縺ｾ縺帙ｓ) */
define('DB_COLLATE', '');

/**#@+
 * 隱崎ｨｼ逕ｨ繝ｦ繝九・繧ｯ繧ｭ繝ｼ
 *
 * 縺昴ｌ縺槭ｌ繧堤焚縺ｪ繧九Θ繝九・繧ｯ (荳諢・ 縺ｪ譁・ｭ怜・縺ｫ螟画峩縺励※縺上□縺輔＞縲・ * {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org 縺ｮ遘伜ｯ・嵯繧ｵ繝ｼ繝薙せ} 縺ｧ閾ｪ蜍慕函謌舌☆繧九％縺ｨ繧ゅ〒縺阪∪縺吶・ * 蠕後〒縺・▽縺ｧ繧ょ､画峩縺励※縲∵里蟄倥・縺吶∋縺ｦ縺ｮ cookie 繧堤┌蜉ｹ縺ｫ縺ｧ縺阪∪縺吶ゅ％繧後↓繧医ｊ縲√☆縺ｹ縺ｦ縺ｮ繝ｦ繝ｼ繧ｶ繝ｼ繧貞ｼｷ蛻ｶ逧・↓蜀阪Ο繧ｰ繧､繝ｳ縺輔○繧九％縺ｨ縺ｫ縺ｪ繧翫∪縺吶・ *
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
 * WordPress 繝・・繧ｿ繝吶・繧ｹ繝・・繝悶Ν縺ｮ謗･鬆ｭ霎・ *
 * 縺昴ｌ縺槭ｌ縺ｫ繝ｦ繝九・繧ｯ (荳諢・ 縺ｪ謗･鬆ｭ霎槭ｒ荳弱∴繧九％縺ｨ縺ｧ荳縺､縺ｮ繝・・繧ｿ繝吶・繧ｹ縺ｫ隍・焚縺ｮ WordPress 繧・ * 繧､繝ｳ繧ｹ繝医・繝ｫ縺吶ｋ縺薙→縺後〒縺阪∪縺吶ょ濠隗定恭謨ｰ蟄励→荳狗ｷ壹・縺ｿ繧剃ｽｿ逕ｨ縺励※縺上□縺輔＞縲・ */
$table_prefix  = 'wp01';

/**
 * 繝ｭ繝ｼ繧ｫ繝ｫ險隱・- 縺薙・繝代ャ繧ｱ繝ｼ繧ｸ縺ｧ縺ｯ蛻晄悄蛟､縺ｨ縺励※ 'ja' (譌･譛ｬ隱・UTF-8) 縺瑚ｨｭ螳壹＆繧後※縺・∪縺吶・ *
 * WordPress 縺ｮ繝ｭ繝ｼ繧ｫ繝ｫ險隱槭ｒ險ｭ螳壹＠縺ｾ縺吶りｨｭ螳壹＠縺溯ｨ隱槭↓蟇ｾ蠢懊☆繧・MO 繝輔ぃ繧､繝ｫ縺・ * wp-content/languages 縺ｫ繧､繝ｳ繧ｹ繝医・繝ｫ縺輔ｌ縺ｦ縺・ｋ蠢・ｦ√′縺ゅｊ縺ｾ縺吶ゆｾ九∴縺ｰ de_DE.mo 繧・ * wp-content/languages 縺ｫ繧､繝ｳ繧ｹ繝医・繝ｫ縺・WPLANG 繧・'de_DE' 縺ｫ險ｭ螳壹☆繧九％縺ｨ縺ｧ繝峨う繝・ｪ槭′繧ｵ繝昴・繝医＆繧後∪縺吶・ */
define('WPLANG', 'ja');

/**
 * 髢狗匱閠・∈: WordPress 繝・ヰ繝・げ繝｢繝ｼ繝・ *
 * 縺薙・蛟､繧・true 縺ｫ縺吶ｋ縺ｨ縲・幕逋ｺ荳ｭ縺ｫ豕ｨ諢・(notice) 繧定｡ｨ遉ｺ縺励∪縺吶・ * 繝・・繝槭♀繧医・繝励Λ繧ｰ繧､繝ｳ縺ｮ髢狗匱閠・↓縺ｯ縲√◎縺ｮ髢狗匱迺ｰ蠅・↓縺翫＞縺ｦ縺薙・ WP_DEBUG 繧剃ｽｿ逕ｨ縺吶ｋ縺薙→繧貞ｼｷ縺乗耳螂ｨ縺励∪縺吶・ */
define('WP_DEBUG', false);

/* 邱ｨ髮・′蠢・ｦ√↑縺ｮ縺ｯ縺薙％縺ｾ縺ｧ縺ｧ縺・! WordPress 縺ｧ繝悶Ο繧ｰ繧偵♀讌ｽ縺励∩縺上□縺輔＞縲・*/

/** Absolute path to the WordPress directory. */
if ( !defined('ABSPATH') )
	define('ABSPATH', dirname(__FILE__) . '/');

/** Sets up WordPress vars and included files. */
require_once(ABSPATH . 'wp-settings.php');
