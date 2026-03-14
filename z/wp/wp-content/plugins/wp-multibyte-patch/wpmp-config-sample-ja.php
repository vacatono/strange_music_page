<?php
/**
 * WordPress 譌･譛ｬ隱樒沿逕ｨ WP Multibyte Patch 險ｭ螳壹ヵ繧｡繧､繝ｫ
 *
 * 縺薙・繝輔ぃ繧､繝ｫ繧貞茜逕ｨ縺励※繝・ヵ繧ｩ繝ｫ繝医・險ｭ螳壼､繧剃ｻｻ諢上↓荳頑嶌縺阪☆繧九％縺ｨ縺後〒縺阪∪縺吶・
 * 險ｭ螳壹ｒ譛牙柑蛹悶☆繧九↓縺ｯ縲∽ｸ玖ｨ倥・蝣ｴ謇縺ｸ縺薙・繝輔ぃ繧､繝ｫ繧貞､牙錐繧ｳ繝斐・縺励※蜀・ｮｹ繧堤ｷｨ髮・＠縺ｦ縺上□縺輔＞縲・
 *
 * /wp-content/wpmp-config.php
 *
 * 繝槭Ν繝√し繧､繝医う繝ｳ繧ｹ繝医・繝ｫ迺ｰ蠅・〒縺ｯ縲∽ｸ玖ｨ倥ヵ繧｡繧､繝ｫ蜷阪↓縺吶ｋ縺薙→縺ｧ蜷・ヶ繝ｭ繧ｰ縺斐→縺ｫ險ｭ螳壹ヵ繧｡繧､繝ｫ繧呈戟縺､縺薙→縺後〒縺阪∪縺吶・
 *
 * /wp-content/wpmp-config-blog-{BLOG ID}.php
 *
 * 險ｭ螳壹・隧ｳ邏ｰ縺ｯ {@link http://eastcoder.com/code/wp-multibyte-patch/} 繧貞盾辣ｧ縺励※縺上□縺輔＞縲・
 *
 * @package WP_Multibyte_Patch
 */

/**
 * 謚慕ｨｿ謚懃ｲ九・譛螟ｧ譁・ｭ玲焚
 *
 * 縺薙・險ｭ螳壹・ the_excerpt() 縺ｨ縺昴・髢｢騾｣縺ｮ謚懃ｲ狗ｳｻ髢｢謨ｰ縺ｫ驕ｩ逕ｨ縺輔ｌ縺ｾ縺吶・
 * 縺薙・險ｭ螳壹・ $wpmp_conf['patch_wp_trim_excerpt'] 縺・false 縺ｮ蝣ｴ蜷医・辟｡蜉ｹ縺ｨ縺ｪ繧翫∪縺吶・
 */
$wpmp_conf['excerpt_mblength'] = 110;

/**
 * 謚慕ｨｿ謚懃ｲ区忰蟆ｾ縺ｫ蜃ｺ蜉帙＆繧後ｋ more 譁・ｭ怜・
 *
 * 縺薙・險ｭ螳壹・ the_excerpt() 縺ｨ縺昴・髢｢騾｣縺ｮ謚懃ｲ狗ｳｻ髢｢謨ｰ縺ｫ驕ｩ逕ｨ縺輔ｌ縺ｾ縺吶・
 * 縺薙・險ｭ螳壹・ $wpmp_conf['patch_wp_trim_excerpt'] 縺・false 縺ｮ蝣ｴ蜷医・辟｡蜉ｹ縺ｨ縺ｪ繧翫∪縺吶・
 */
$wpmp_conf['excerpt_more'] = ' [&hellip;]';

/**
 * get_comment_excerpt() 謚懃ｲ九・譛螟ｧ譁・ｭ玲焚
 *
 * 縺薙・險ｭ螳壹・ comment_excerpt() (繝繝・す繝･繝懊・繝・> 繧｢繧ｯ繝・ぅ繝薙ユ繧｣ > 繧ｳ繝｡繝ｳ繝・縺ｮ謚懃ｲ九〒蛻ｩ逕ｨ) 縺ｫ驕ｩ逕ｨ縺輔ｌ縺ｾ縺吶・
 * 縺薙・險ｭ螳壹・ $wpmp_conf['patch_get_comment_excerpt'] 縺・false 縺ｮ蝣ｴ蜷医・辟｡蜉ｹ縺ｨ縺ｪ繧翫∪縺吶・
 */
$wpmp_conf['comment_excerpt_mblength'] = 40;

/**
 * 繝繝・す繝･繝懊・繝峨御ｸ区嶌縺阪肴栢邊九・譛螟ｧ譁・ｭ玲焚
 *
 * 縺薙・險ｭ螳壹・縲√ム繝・す繝･繝懊・繝・> 繧ｯ繧､繝・け繝峨Λ繝輔ヨ > 荳区嶌縺・縺ｮ謚懃ｲ九↓驕ｩ逕ｨ縺輔ｌ縺ｾ縺吶・
 * 縺薙・險ｭ螳壹・ $wpmp_conf['patch_dashboard_recent_drafts'] 縺・false 縺ｮ蝣ｴ蜷医・辟｡蜉ｹ縺ｨ縺ｪ繧翫∪縺吶・
 */
$wpmp_conf['dashboard_recent_drafts_mblength'] = 40;

/**
 * wp_mail() 縺ｮ譁・ｭ励お繝ｳ繧ｳ繝ｼ繝・ぅ繝ｳ繧ｰ
 *
 * 縺薙・險ｭ螳壹・ WordPress 縺九ｉ wp_mail() 繧帝壹＠縺ｦ騾∽ｿ｡縺輔ｌ繧九Γ繝ｼ繝ｫ縺ｫ驕ｩ逕ｨ縺輔ｌ縺ｾ縺吶・
 * 謖・ｮ壼庄閭ｽ縺ｪ蛟､縺ｯ縲・JIS'縲・UTF-8'縲・auto' 縺ｧ縺吶・
 * 縺薙・險ｭ螳壹・ $wpmp_conf['patch_wp_mail'] 縺・false 縺ｮ蝣ｴ蜷医・辟｡蜉ｹ縺ｨ縺ｪ繧翫∪縺吶・
 */
$wpmp_conf['mail_mode'] = 'JIS';

/**
 * 邂｡逅・ヱ繝阪Ν繧ｫ繧ｹ繧ｿ繝 CSS 縺ｮ URL
 *
 * 邂｡逅・ヱ繝阪Ν縺ｧ隱ｭ縺ｿ霎ｼ縺ｾ繧後ｋ CSS 縺ｮ URL 繧剃ｻｻ諢上〒謖・ｮ壹☆繧九％縺ｨ縺後〒縺阪∪縺吶・
 * 譛ｪ謖・ｮ壹・蝣ｴ蜷医・縲√ョ繝輔か繝ｫ繝医・ CSS 縺瑚ｪｭ縺ｿ霎ｼ縺ｾ繧後∪縺吶・
 * 縺薙・險ｭ螳壹・ $wpmp_conf['patch_admin_custom_css'] 縺・false 縺ｮ蝣ｴ蜷医・辟｡蜉ｹ縺ｨ縺ｪ繧翫∪縺吶・
 */
$wpmp_conf['admin_custom_css_url'] = '';

/**
 * BuddyPress bp_create_excerpt() 謚懃ｲ九・譛螟ｧ譁・ｭ玲焚
 *
 * 縺薙・險ｭ螳壹・ BuddyPress 縺ｮ bp_create_excerpt() (繧｢繧ｯ繝・ぅ繝薙ユ繧｣繧ｹ繝医Μ繝ｼ繝縺ｮ謚懃ｲ九〒蛻ｩ逕ｨ) 縺ｫ驕ｩ逕ｨ縺輔ｌ縺ｾ縺吶・
 * 縺薙・險ｭ螳壹・ $wpmp_conf['patch_bp_create_excerpt'] 縺・false 縺ｮ蝣ｴ蜷医・辟｡蜉ｹ縺ｨ縺ｪ繧翫∪縺吶・
 */
$wpmp_conf['bp_excerpt_mblength'] = 110;

/**
 * BuddyPress bp_create_excerpt() 謚懃ｲ区忰蟆ｾ縺ｫ蜃ｺ蜉帙＆繧後ｋ more 譁・ｭ怜・
 *
 * 縺薙・險ｭ螳壹・ BuddyPress 縺ｮ bp_create_excerpt() (繧｢繧ｯ繝・ぅ繝薙ユ繧｣繧ｹ繝医Μ繝ｼ繝縺ｮ謚懃ｲ九〒蛻ｩ逕ｨ) 縺ｫ驕ｩ逕ｨ縺輔ｌ縺ｾ縺吶・
 * 縺薙・險ｭ螳壹・ $wpmp_conf['patch_bp_create_excerpt'] 縺・false 縺ｮ蝣ｴ蜷医・辟｡蜉ｹ縺ｨ縺ｪ繧翫∪縺吶・
 */
$wpmp_conf['bp_excerpt_more'] = ' [&hellip;]';


/* 讖溯・繧貞句挨縺ｫ譛牙柑蛹悶∫┌蜉ｹ蛹悶〒縺阪∪縺吶よ怏蜉ｹ蛹悶☆繧九↓縺ｯ true 繧偵∫┌蜉ｹ蛹悶☆繧九↓縺ｯ false 繧呈欠螳壹＠縺ｦ縺上□縺輔＞縲・*/
$wpmp_conf['patch_wp_mail'] = true;
$wpmp_conf['patch_incoming_trackback'] = true;
$wpmp_conf['patch_incoming_pingback'] = true;
$wpmp_conf['patch_wp_trim_excerpt'] = true;
$wpmp_conf['patch_wp_trim_words'] = true;
$wpmp_conf['patch_get_comment_excerpt'] = true;
$wpmp_conf['patch_dashboard_recent_drafts'] = true;
$wpmp_conf['patch_process_search_terms'] = true;
$wpmp_conf['patch_admin_custom_css'] = true;
$wpmp_conf['patch_wplink_js'] = true;
$wpmp_conf['patch_force_character_count'] = true;
$wpmp_conf['patch_force_twentytwelve_open_sans_off'] = true;
$wpmp_conf['patch_force_twentythirteen_google_fonts_off'] = false;
$wpmp_conf['patch_force_twentyfourteen_google_fonts_off'] = false;
$wpmp_conf['patch_force_twentyfifteen_google_fonts_off'] = false;
$wpmp_conf['patch_force_twentysixteen_google_fonts_off'] = false;
$wpmp_conf['patch_force_twentyseventeen_google_fonts_off'] = false;
$wpmp_conf['patch_sanitize_file_name'] = true;
$wpmp_conf['patch_sanitize_feed_xml_text'] = false;
$wpmp_conf['patch_bp_create_excerpt'] = false;
