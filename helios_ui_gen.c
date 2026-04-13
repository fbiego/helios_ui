/**
 * @file helios_ui_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "helios_ui_gen.h"

#if LV_USE_XML
#include "widgets/wd_arcoiris/wd_arcoiris_private_gen.h"
#include "widgets/wd_dropdown/wd_dropdown_private_gen.h"
#include "widgets/wd_image/wd_image_private_gen.h"
#include "widgets/wd_list/wd_list_private_gen.h"
#include "widgets/wd_segment/wd_segment_private_gen.h"
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/*----------------
 * Translations
 *----------------*/

#ifndef LV_EDITOR_PREVIEW
    static const char * translation_languages[] = {"en", "pt", "de", "es", "fr", "hu", "ru", "el", "th", "zh", "ja", "hi", NULL};
    static const char * translation_tags[] = {"id", "locale", "sun", "mon", "tue", "wed", "thur", "fri", "sat", "jan", "feb", "mar", "apr", "jun", "jul", "aug", "sept", "oct", "nov", "dec", "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december", "contacts", "files", "fitness", "health", "music", "navigation", "notifications", "settings", "sleep", "stopwatch", "timer", "weather", "display", "system", "alerts", "battery", "about", "storage", "brightness", "timeout", "rotation", "raise_to_wake", "circular_scroll", "grid_mode", "language", "reboot", "shutdown", "factory_reset", "sound", "vibration", "wake_screen", "dnd", "voltage", "temperature", "usage", "format", "firmware", "hourly_forecast", "daily_forecast", "timeout_5", "timeout_10", "timeout_20", "timeout_30", "always_on", NULL};
    static const char * translation_texts[] = {
        "en", "pt", "de", "es", "fr", "hu", "ru", "el", "th", "zh", "ja", "hi", /* id */
        "English", "Portuguese", "German", "Spanish", "French", "Hungarian", "Russian", "Greek", "Thai", "Chinese", "Japanese", "Hindi", /* locale */
        "Sun", "Sol", "Sonne", "Sol", "Soleil", "Nap", "Солнце", "Ήλιος", "ดวงอาทิตย์", "太阳", "太陽", "सूरज", /* sun */
        "Mon", "seg", "Montag", "Lun", "Lun", "Hétfő", "Пн", "Δευ", "จันทร์", "星期一", "月曜日", "सोमवार", /* mon */
        "Tue", "ter", "Di.", "Mar", "Mar", "Kedd", "Вт", "Τρί", "อังคาร", "星期二", "火曜日", "मंगल", /* tue */
        "Wed", "qua", "Heiraten", "Casarse", "Épouser", "Házasodik", "Обвенчались", "Νυμφεύομαι", "วันพุธ", "星期三", "水曜日", "बुधवार", /* wed */
        "Thur", "Quinta-feira", "Donnerstag", "Jueves", "Jeu", "Csütörtök", "Чт", "Πέμ", "วันพฤหัสบดี", "周四", "木曜日", "गुरु", /* thur */
        "Fri", "sex", "Freitag", "Vie", "Ven", "Péntek", "Пятница", "Παρ", "ศุกร์", "星期五", "金曜日", "शुक्र", /* fri */
        "Sat", "Sentado", "Sa", "Se sentó", "Assis", "Ült", "Сб", "Σάβ", "นั่ง", "星期六", "土曜日", "बैठा", /* sat */
        "Jan", "janeiro", "Januar", "Ene", "Jan", "Január", "Янв", "Ιαν", "ม.ค", "一月", "ジャン", "जनवरी", /* jan */
        "Feb", "fevereiro", "Februar", "Feb", "Fév", "Február", "февраль", "Φεβ", "กุมภาพันธ์", "二月", "2月", "फ़रवरी", /* feb */
        "Mar", "Mar", "Beschädigen", "Mar", "Mar", "Március", "март", "Αφανίζω", "มีนาคม", "三月", "3月", "मार्च", /* mar */
        "Apr", "abril", "April", "Abr", "Avr", "Április", "Апр", "Απρ", "เมษายน", "四月", "4月", "अप्रैल", /* apr */
        "Jun", "junho", "Juni", "Jun", "Juin", "Június", "Джун", "Ιούνιος", "จุน", "俊", "ジュン", "जून", /* jun */
        "Jul", "julho", "Jul", "Jul", "Juillet", "Július", "июль", "Ιούλ", "กรกฎาคม", "七月", "7月", "जुलाई", /* jul */
        "Aug", "agosto", "August", "Ago", "Août", "Augusztus", "Август", "Αυγ", "ส.ค.", "八月", "8月", "अगस्त", /* aug */
        "Sep", "Setembro", "September", "Sep", "Sep", "Szept.", "Сентябрь", "Σεπ", "กันยายน", "九月", "9月", "सितम्बर", /* sept */
        "Oct", "Outubro", "Oktober", "Oct", "Octobre", "Október", "Октябрь", "Οκτ", "ตุลาคม", "十月", "10月", "अक्टूबर", /* oct */
        "Nov", "novembro", "November", "Nov", "Nov", "November", "Ноябрь", "Νοέμβριος", "พฤศจิกายน", "十一月", "11月", "नवंबर", /* nov */
        "Dec", "Dezembro", "Dezember", "Dic", "Déc", "December", "Декабрь", "Δεκ", "ธันวาคม", "12月", "12月", "दिसम्बर", /* dec */
        "Sunday", "Domingo", "Sonntag", "Domingo", "Dimanche", "vasárnap", "Воскресенье", "Κυριακή", "วันอาทิตย์", "星期日", "日曜日", "रविवार", /* sunday */
        "Monday", "Segunda-feira", "Montag", "Lunes", "Lundi", "hétfő", "Понедельник", "Δευτέρα", "วันจันทร์", "周一", "月曜日", "सोमवार", /* monday */
        "Tuesday", "Terça-feira", "Dienstag", "Martes", "Mardi", "kedd", "Вторник", "Τρίτη", "วันอังคาร", "周二", "火曜日", "मंगलवार", /* tuesday */
        "Wednesday", "Quarta-feira", "Mittwoch", "Miércoles", "Mercredi", "szerda", "Среда", "Τετάρτη", "วันพุธ", "周三", "水曜日", "बुधवार", /* wednesday */
        "Thursday", "Quinta-feira", "Donnerstag", "Jueves", "Jeudi", "csütörtök", "Четверг", "Πέμπτη", "วันพฤหัสบดี", "周四", "木曜日", "गुरुवार", /* thursday */
        "Friday", "Sexta-feira", "Freitag", "Viernes", "Vendredi", "péntek", "Пятница", "Παρασκευή", "วันศุกร์", "星期五", "金曜日", "शुक्रवार", /* friday */
        "Saturday", "Sábado", "Samstag", "Sábado", "Samedi", "szombat", "Суббота", "Σάββατο", "วันเสาร์", "周六", "土曜日", "शनिवार", /* saturday */
        "January", "Janeiro", "Januar", "Enero", "Janvier", "január", "Январь", "Ιανουάριος", "มกราคม", "一月", "1月", "जनवरी", /* january */
        "February", "Fevereiro", "Februar", "Febrero", "Février", "február", "Февраль", "Φεβρουάριος", "กุมภาพันธ์", "二月", "2月", "फ़रवरी", /* february */
        "March", "Marchar", "Marsch", "Marzo", "Mars", "március", "Маршировать", "Πορεία", "มีนาคม", "行进", "行進", "मार्च", /* march */
        "April", "abril", "April", "Abril", "Avril", "április", "Апрель", "Απρίλιος", "เมษายน", "四月", "4月", "अप्रैल", /* april */
        "May", "Poderia", "Mai", "Puede", "Peut", "május", "Может", "Μάιος", "อาจ", "可能", "5月", "मई", /* may */
        "June", "Junho", "Juni", "Junio", "Juin", "június", "Июнь", "Ιούνιος", "มิถุนายน", "六月", "6月", "जून", /* june */
        "July", "Julho", "Juli", "Julio", "Juillet", "július", "Июль", "Ιούλιος", "กรกฎาคม", "七月", "7月", "जुलाई", /* july */
        "August", "Agosto", "August", "Agosto", "Août", "augusztus", "Август", "Αύγουστος", "สิงหาคม", "八月", "8月", "अगस्त", /* august */
        "September", "Setembro", "September", "Septiembre", "Septembre", "szeptember", "Сентябрь", "Σεπτέμβριος", "กันยายน", "九月", "9月", "सितम्बर", /* september */
        "October", "outubro", "Oktober", "Octubre", "Octobre", "október", "Октябрь", "Οκτώβριος", "ตุลาคม", "十月", "10月", "अक्टूबर", /* october */
        "November", "novembro", "November", "Noviembre", "Novembre", "november", "Ноябрь", "Νοέμβριος", "พฤศจิกายน", "十一月", "11月", "नवंबर", /* november */
        "December", "dezembro", "Dezember", "Diciembre", "Décembre", "december", "Декабрь", "Δεκέμβριος", "ธันวาคม", "十二月", "12月", "दिसंबर", /* december */
        "Contacts", "Contatos", "Kontakte", "Contactos", "Contacts", "Kapcsolatok", "Контакты", "Επαφές", "การติดต่อ", "联系方式", "連絡先", "संपर्क", /* contacts */
        "Files", "Arquivos", "Dateien", "Archivos", "Fichiers", "Fájlok", "Файлы", "Αρχεία", "ไฟล์", "文件", "ファイル", "फ़ाइलें", /* files */
        "Fitness", "Fitness", "Fitness", "Aptitud física", "Aptitude", "Fitnesz", "Фитнес", "Καταλληλότητα", "ฟิตเนส", "健康", "フィットネス", "स्वास्थ्य", /* fitness */
        "Health", "Saúde", "Gesundheit", "Salud", "Santé", "Egészség", "Здоровье", "Υγεία", "สุขภาพ", "健康", "健康", "स्वास्थ्य", /* health */
        "Music", "Música", "Musik", "Música", "Musique", "Zene", "Музыка", "Μουσική", "ดนตรี", "音乐", "音楽", "संगीत", /* music */
        "Navigation", "Navegação", "Navigation", "Navegación", "Navigation", "Navigáció", "Навигация", "Πλοήγηση", "การนำทาง", "导航", "ナビゲーション", "मार्गदर्शन", /* navigation */
        "Notifications", "Notificações", "Benachrichtigungen", "Notificaciones", "Notifications", "Értesítések", "Уведомления", "Ειδοποιήσεις", "การแจ้งเตือน", "通知", "通知", "सूचनाएं", /* notifications */
        "Settings", "Configurações", "Einstellungen", "Ajustes", "Paramètres", "Beállítások", "Настройки", "Ρυθμίσεις", "การตั้งค่า", "设置", "設定", "सेटिंग्स", /* settings */
        "Sleep", "Dormir", "Schlafen", "Dormir", "Dormir", "Alvás", "Спать", "Υπνος", "นอน", "睡觉", "寝る", "नींद", /* sleep */
        "Stopwatch", "Cronômetro", "Stoppuhr", "Cronógrafo", "Chronomètre", "Stopperóra", "Секундомер", "Χρονόμετρο", "นาฬิกาจับเวลา", "跑表", "ストップウォッチ", "स्टॉपवॉच देखनी", /* stopwatch */
        "Timer", "Temporizador", "Timer", "Minutero", "Minuteur", "Időzítő", "Таймер", "Μετρών την ώραν", "ตัวจับเวลา", "定时器", "タイマー", "घड़ी", /* timer */
        "Weather", "Clima", "Wetter", "Clima", "Météo", "Időjárás", "Погода", "Καιρός", "สภาพอากาศ", "天气", "天気", "मौसम", /* weather */
        "Display", "Mostrar", "Anzeige", "Mostrar", "Afficher", "Kijelző", "Отображать", "Επίδειξη", "แสดง", "展示", "画面", "प्रदर्शन", /* display */
        "System", "Sistema", "System", "Sistema", "Système", "Rendszer", "Система", "Σύστημα", "ระบบ", "系统", "システム", "प्रणाली", /* system */
        "Alerts", "Alertas", "Warnmeldungen", "Alertas", "Alertes", "Riasztások", "Оповещения", "Ειδοποιήσεις", "การแจ้งเตือน", "警报", "アラート", "अलर्ट", /* alerts */
        "Battery", "Bateria", "Batterie", "Batería", "Batterie", "Akkumulátor", "Батарея", "Μπαταρία", "แบตเตอรี่", "电池", "バッテリー", "बैटरी", /* battery */
        "About", "Sobre", "Um", "Acerca de", "À propos", "Körülbelül", "О", "Για", "เกี่ยวกับ", "关于", "について", "के बारे में", /* about */
        "Storage", "Armazenar", "Lagerung", "Almacenamiento", "Stockage", "Tárolás", "Хранилище", "Αποθήκευση", "พื้นที่จัดเก็บ", "贮存", "ストレージ", "भंडारण", /* storage */
        "Brightness", "Brilho", "Helligkeit", "Brillo", "Luminosité", "Fényesség", "Яркость", "Λάμψη", "ความสว่าง", "亮度", "輝度", "चमक", /* brightness */
        "Timeout", "Tempo esgotado", "Time-out", "Se acabó el tiempo", "Temps mort", "Időtúllépés", "Тайм-аут", "Χρονικό όριο", "หมดเวลา", "暂停", "タイムアウト", "समय समाप्त", /* timeout */
        "Rotation", "Rotação", "Drehung", "Rotación", "Rotation", "Forgás", "Вращение", "Περιστροφή", "การหมุน", "旋转", "回転", "ROTATION", /* rotation */
        "Raise to wake", "Levante para acordar", "Zum Aufwecken hochziehen", "Levantarse para despertar", "Lever pour réveiller", "Ébredés", "Поднимитесь, чтобы проснуться", "Σήκωσε για να ξυπνήσεις", "ยกขึ้นเพื่อปลุก", "起身唤醒", "起こすために持ち上げる", "जगाने के लिए उठाएँ", /* raise_to_wake */
        "Circular scroll", "Pergaminho circular", "Kreisförmige Schriftrolle", "Pergamino circular", "rouleau circulaire", "Kör alakú görgetés", "Круглый свиток", "Κυκλική κύλιση", "ม้วนกลม", "圆形卷轴", "円形スクロール", "वृत्ताकार स्क्रॉल", /* circular_scroll */
        "Grid mode", "Modo de grade", "Rastermodus", "Modo cuadrícula", "Mode grille", "Rács mód", "Режим сетки", "Λειτουργία πλέγματος", "โหมดตาราง", "网格模式", "グリッドモード", "ग्रिड मोड", /* grid_mode */
        "Language", "Linguagem", "Sprache", "Idioma", "Langue", "Nyelv", "Язык", "Γλώσσα", "ภาษา", "语言", "言語", "भाषा", /* language */
        "Reboot", "Reinício", "Neustart", "Reiniciar", "Redémarrage", "Újraindítás", "Перезагрузить", "Επανεκκίνηση", "รีบูต", "重启", "リブート", "रीबूट", /* reboot */
        "Shutdown", "Desligar", "Abschalten", "Cerrar", "Fermer", "Leállítás", "Неисправность", "Κλείσιμο", "ปิดระบบ", "关闭", "シャットダウン", "शट डाउन", /* shutdown */
        "Factory Reset", "Restauração de fábrica", "Werksreset", "Restablecimiento de fábrica", "Réinitialisation d\'usine", "Gyári visszaállítás", "Сброс к заводским настройкам", "Επαναφορά εργοστασιακών ρυθμίσεων", "รีเซ็ตเป็นค่าจากโรงงาน", "恢复出厂设置", "工場出荷時設定にリセット", "नए यंत्र जैसी सेटिंग", /* factory_reset */
        "Sound", "Som", "Klang", "Sonido", "Son", "Hang", "Звук", "Ήχος", "เสียง", "声音", "音", "आवाज़", /* sound */
        "Vibration", "Vibração", "Vibration", "Vibración", "Vibration", "Rezgés", "Вибрация", "Δόνηση", "การสั่นสะเทือน", "振动", "振動", "कंपन", /* vibration */
        "Wake screen", "Tela de ativação", "Bildschirm aufwecken", "Pantalla de activación", "Écran de réveil", "Képernyő felébresztése", "Экран пробуждения", "Οθόνη αφύπνισης", "หน้าจอปลุก", "唤醒屏幕", "起動画面", "जाग्रत स्क्रीन", /* wake_screen */
        "DND", "Não perturbe", "DND", "Ministerio de Defensa Nacional", "DND", "Ne zavarj", "ДНД", "Μην ανησυχείτε", "ห้ามรบกวน", "DND", "D&D", "डीएनडी", /* dnd */
        "Voltage", "Tensão", "Stromspannung", "Voltaje", "Tension", "Feszültség", "Напряжение", "Δυναμικό", "แรงดันไฟฟ้า", "电压", "電圧", "वोल्टेज", /* voltage */
        "Temperatue", "Temperatura", "Temperatur", "Temperatura", "Température", "Hőmérséklet", "Температура", "Θερμοκρασία", "อุณหภูมิ", "温度", "温度", "तापमान", /* temperature */
        "Usage", "Uso", "Verwendung", "Uso", "Usage", "Használat", "Использование", "Χρήση", "การใช้งาน", "用法", "使用法", "प्रयोग", /* usage */
        "Format", "Formatar", "Format", "Formato", "Format", "Formátum", "Формат", "Σχήμα και διάταξις βιβλίου", "รูปแบบ", "格式", "形式", "प्रारूप", /* format */
        "Firmware", "Firmware", "Firmware", "Firmware", "Micrologiciel", "Firmware", "Прошивка", "Υλικολογισμικό", "เฟิร์มแวร์", "固件", "ファームウェア", "फर्मवेयर", /* firmware */
        "Hourly Forecast", "Previsão horária", "Stündliche Vorhersage", "Pronóstico por hora", "Prévisions horaires", "Óránkénti előrejelzés", "Почасовой прогноз", "Ωριαία Πρόβλεψη", "พยากรณ์อากาศรายชั่วโมง", "逐小时预报", "時間別予報", "घंटेवार पूर्वानुमान", /* hourly_forecast */
        "Daily Forecast", "Previsão diária", "Tagesvorhersage", "Pronóstico diario", "Prévisions quotidiennes", "Napi előrejelzés", "Ежедневный прогноз", "Ημερήσια Πρόγνωση", "พยากรณ์อากาศประจำวัน", "每日天气预报", "日々の天気予報", "दैनिक पूर्वानुमान", /* daily_forecast */
        "5 seconds", "5 segundos", "5 Sekunden", "5 segundos", "5 secondes", "5 másodperc", "5 секунд", "5 δευτερόλεπτα", "5 วินาที", "5秒", "5秒", "5 सेकंड", /* timeout_5 */
        "10 seconds", "10 segundos", "10 Sekunden", "10 segundos", "10 secondes", "10 másodperc", "10 секунд", "10 δευτερόλεπτα", "10 วินาที", "10秒", "10秒", "10 सेकंड", /* timeout_10 */
        "20 seconds", "20 segundos", "20 Sekunden", "20 segundos", "20 secondes", "20 másodperc", "20 секунд", "20 δευτερόλεπτα", "20 วินาที", "20秒", "20秒", "20 सेकंड", /* timeout_20 */
        "30 seconds", "30 segundos", "30 Sekunden", "30 segundos", "30 secondes", "30 másodperc", "30 секунд", "30 δευτερόλεπτα", "30 วินาที", "30秒", "30秒", "30 सेकंड", /* timeout_30 */
        "Always On", "Sempre ligado", "Immer eingeschaltet", "Siempre encendido", "Toujours allumé", "Mindig bekapcsolva", "Всегда включено", "Πάντα ενεργοποιημένο", "เปิดใช้งานตลอดเวลา", "始终开启", "常時接続", "हमेशा बने रहें", /* always_on */
    };
#endif

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Fonts
 *----------------*/

lv_font_t * NS_Medium_14;
extern lv_font_t NS_Medium_14_data;
lv_font_t * NS_Medium_16;
extern lv_font_t NS_Medium_16_data;
lv_font_t * NS_Medium_18;
extern lv_font_t NS_Medium_18_data;
lv_font_t * NS_Medium_20;
extern lv_font_t NS_Medium_20_data;
lv_font_t * NS_Medium_30;
extern lv_font_t NS_Medium_30_data;
lv_font_t * NS_Medium_40;
extern lv_font_t NS_Medium_40_data;
lv_font_t * NS_Medium_70;
extern lv_font_t NS_Medium_70_data;
lv_font_t * NS_Medium_100;
extern lv_font_t NS_Medium_100_data;
lv_font_t * NS_Medium_140;
extern lv_font_t NS_Medium_140_data;
lv_font_t * NS_Medium_latin_14;
extern lv_font_t NS_Medium_latin_14_data;
lv_font_t * NS_Medium_latin_16;
extern lv_font_t NS_Medium_latin_16_data;
lv_font_t * NS_Medium_latin_18;
extern lv_font_t NS_Medium_latin_18_data;
lv_font_t * NS_Medium_latin_20;
extern lv_font_t NS_Medium_latin_20_data;
lv_font_t * NS_Medium_latin_30;
extern lv_font_t NS_Medium_latin_30_data;
lv_font_t * NS_Medium_latin_40;
extern lv_font_t NS_Medium_latin_40_data;
lv_font_t * NS_Medium_ru_14;
extern lv_font_t NS_Medium_ru_14_data;
lv_font_t * NS_Medium_ru_16;
extern lv_font_t NS_Medium_ru_16_data;
lv_font_t * NS_Medium_ru_18;
extern lv_font_t NS_Medium_ru_18_data;
lv_font_t * NS_Medium_ru_20;
extern lv_font_t NS_Medium_ru_20_data;
lv_font_t * NS_Medium_ru_30;
extern lv_font_t NS_Medium_ru_30_data;
lv_font_t * NS_Medium_ru_40;
extern lv_font_t NS_Medium_ru_40_data;
lv_font_t * NS_Medium_el_14;
extern lv_font_t NS_Medium_el_14_data;
lv_font_t * NS_Medium_el_16;
extern lv_font_t NS_Medium_el_16_data;
lv_font_t * NS_Medium_el_18;
extern lv_font_t NS_Medium_el_18_data;
lv_font_t * NS_Medium_el_20;
extern lv_font_t NS_Medium_el_20_data;
lv_font_t * NS_Medium_el_30;
extern lv_font_t NS_Medium_el_30_data;
lv_font_t * NS_Medium_el_40;
extern lv_font_t NS_Medium_el_40_data;
lv_font_t * NS_Medium_hi_14;
extern lv_font_t NS_Medium_hi_14_data;
lv_font_t * NS_Medium_hi_16;
extern lv_font_t NS_Medium_hi_16_data;
lv_font_t * NS_Medium_hi_18;
extern lv_font_t NS_Medium_hi_18_data;
lv_font_t * NS_Medium_hi_20;
extern lv_font_t NS_Medium_hi_20_data;
lv_font_t * NS_Medium_hi_30;
extern lv_font_t NS_Medium_hi_30_data;
lv_font_t * NS_Medium_hi_40;
extern lv_font_t NS_Medium_hi_40_data;
lv_font_t * NS_Medium_th_14;
extern lv_font_t NS_Medium_th_14_data;
lv_font_t * NS_Medium_th_16;
extern lv_font_t NS_Medium_th_16_data;
lv_font_t * NS_Medium_th_18;
extern lv_font_t NS_Medium_th_18_data;
lv_font_t * NS_Medium_th_20;
extern lv_font_t NS_Medium_th_20_data;
lv_font_t * NS_Medium_th_30;
extern lv_font_t NS_Medium_th_30_data;
lv_font_t * NS_Medium_th_40;
extern lv_font_t NS_Medium_th_40_data;
lv_font_t * NS_Medium_zh_14;
extern lv_font_t NS_Medium_zh_14_data;
lv_font_t * NS_Medium_zh_16;
extern lv_font_t NS_Medium_zh_16_data;
lv_font_t * NS_Medium_zh_18;
extern lv_font_t NS_Medium_zh_18_data;
lv_font_t * NS_Medium_zh_20;
extern lv_font_t NS_Medium_zh_20_data;
lv_font_t * NS_Medium_zh_30;
extern lv_font_t NS_Medium_zh_30_data;
lv_font_t * NS_Medium_zh_40;
extern lv_font_t NS_Medium_zh_40_data;
lv_font_t * NS_Medium_jp_14;
extern lv_font_t NS_Medium_jp_14_data;
lv_font_t * NS_Medium_jp_16;
extern lv_font_t NS_Medium_jp_16_data;
lv_font_t * NS_Medium_jp_18;
extern lv_font_t NS_Medium_jp_18_data;
lv_font_t * NS_Medium_jp_20;
extern lv_font_t NS_Medium_jp_20_data;
lv_font_t * NS_Medium_jp_30;
extern lv_font_t NS_Medium_jp_30_data;
lv_font_t * NS_Medium_jp_40;
extern lv_font_t NS_Medium_jp_40_data;

/*----------------
 * Images
 *----------------*/

const void * icon_empty;
extern const void * icon_empty_data;
const void * icon_wifi;
extern const void * icon_wifi_data;
const void * icon_list;
extern const void * icon_list_data;
const void * icon_brightness_full;
extern const void * icon_brightness_full_data;
const void * icon_brightness_empty;
extern const void * icon_brightness_empty_data;
const void * icon_volume_high;
extern const void * icon_volume_high_data;
const void * icon_volume_low;
extern const void * icon_volume_low_data;
const void * icon_mute;
extern const void * icon_mute_data;
const void * icon_play;
extern const void * icon_play_data;
const void * icon_back;
extern const void * icon_back_data;
const void * icon_next;
extern const void * icon_next_data;
const void * icon_connect;
extern const void * icon_connect_data;
const void * icon_vibration;
extern const void * icon_vibration_data;
const void * icon_dnd;
extern const void * icon_dnd_data;
const void * icon_qr;
extern const void * icon_qr_data;
const void * icon_arrow_up;
extern const void * icon_arrow_up_data;
const void * icon_settings_harddisk;
extern const void * icon_settings_harddisk_data;
const void * icon_settings_brightness;
extern const void * icon_settings_brightness_data;
const void * icon_settings_monitor;
extern const void * icon_settings_monitor_data;
const void * icon_settings_information;
extern const void * icon_settings_information_data;
const void * icon_settings_smartwatch;
extern const void * icon_settings_smartwatch_data;
const void * icon_settings_rotate;
extern const void * icon_settings_rotate_data;
const void * icon_settings_power;
extern const void * icon_settings_power_data;
const void * icon_settings_bell;
extern const void * icon_settings_bell_data;
const void * icon_application;
extern const void * icon_application_data;
const void * icon_chat;
extern const void * icon_chat_data;
const void * icon_weather;
extern const void * icon_weather_data;
const void * icon_gear;
extern const void * icon_gear_data;
const void * icon_measurement;
extern const void * icon_measurement_data;
const void * icon_stopwatch;
extern const void * icon_stopwatch_data;
const void * icon_contacts;
extern const void * icon_contacts_data;
const void * icon_navigation;
extern const void * icon_navigation_data;
const void * icon_timer;
extern const void * icon_timer_data;
const void * icon_music;
extern const void * icon_music_data;
const void * icon_folder;
extern const void * icon_folder_data;
const void * icon_running;
extern const void * icon_running_data;
const void * icon_sleep;
extern const void * icon_sleep_data;
const void * icon_weather_humidity_icon;
extern const void * icon_weather_humidity_icon_data;
const void * icon_weather_temp_up_icon;
extern const void * icon_weather_temp_up_icon_data;
const void * icon_weather_temp_down_icon;
extern const void * icon_weather_temp_down_icon_data;
const void * icon_weather_uv_icon;
extern const void * icon_weather_uv_icon_data;

/*----------------
 * Global styles
 *----------------*/

lv_style_t style_dark;
lv_style_t style_primary_bg;
lv_style_t style_white_bg;
lv_style_t style_icon_recolor;
lv_style_t style_text_small_466;
lv_style_t style_text_small_360;
lv_style_t style_text_small_240;
lv_style_t style_text_normal_466;
lv_style_t style_text_normal_360;
lv_style_t style_text_normal_240;
lv_style_t style_text_large_466;
lv_style_t style_text_large_360;
lv_style_t style_text_large_240;

/*----------------
 * Subjects
 *----------------*/

lv_subject_t sb_screen_size;
lv_subject_t sb_screen_type;
lv_subject_t sb_app_list_mode;
lv_subject_t sb_list_circular_mode;
lv_subject_t sb_screen_brightness;
lv_subject_t sb_screen_rotation;
lv_subject_t sb_screen_timeout;
lv_subject_t sb_screen_rtw;
lv_subject_t sb_language;
lv_subject_t sb_battery_percent;
lv_subject_t sb_sound_volume;
lv_subject_t sb_focusable;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void helios_ui_init_gen(const char * asset_path)
{
    char buf[256];


    /*----------------
     * Fonts
     *----------------*/

    /* get font 'NS_Medium_14' from a C array */
    NS_Medium_14 = &NS_Medium_14_data;
    /* get font 'NS_Medium_16' from a C array */
    NS_Medium_16 = &NS_Medium_16_data;
    /* get font 'NS_Medium_18' from a C array */
    NS_Medium_18 = &NS_Medium_18_data;
    /* get font 'NS_Medium_20' from a C array */
    NS_Medium_20 = &NS_Medium_20_data;
    /* get font 'NS_Medium_30' from a C array */
    NS_Medium_30 = &NS_Medium_30_data;
    /* get font 'NS_Medium_40' from a C array */
    NS_Medium_40 = &NS_Medium_40_data;
    /* get font 'NS_Medium_70' from a C array */
    NS_Medium_70 = &NS_Medium_70_data;
    /* get font 'NS_Medium_100' from a C array */
    NS_Medium_100 = &NS_Medium_100_data;
    /* get font 'NS_Medium_140' from a C array */
    NS_Medium_140 = &NS_Medium_140_data;
    /* get font 'NS_Medium_latin_14' from a C array */
    NS_Medium_latin_14 = &NS_Medium_latin_14_data;
    /* get font 'NS_Medium_latin_16' from a C array */
    NS_Medium_latin_16 = &NS_Medium_latin_16_data;
    /* get font 'NS_Medium_latin_18' from a C array */
    NS_Medium_latin_18 = &NS_Medium_latin_18_data;
    /* get font 'NS_Medium_latin_20' from a C array */
    NS_Medium_latin_20 = &NS_Medium_latin_20_data;
    /* get font 'NS_Medium_latin_30' from a C array */
    NS_Medium_latin_30 = &NS_Medium_latin_30_data;
    /* get font 'NS_Medium_latin_40' from a C array */
    NS_Medium_latin_40 = &NS_Medium_latin_40_data;
    /* get font 'NS_Medium_ru_14' from a C array */
    NS_Medium_ru_14 = &NS_Medium_ru_14_data;
    /* get font 'NS_Medium_ru_16' from a C array */
    NS_Medium_ru_16 = &NS_Medium_ru_16_data;
    /* get font 'NS_Medium_ru_18' from a C array */
    NS_Medium_ru_18 = &NS_Medium_ru_18_data;
    /* get font 'NS_Medium_ru_20' from a C array */
    NS_Medium_ru_20 = &NS_Medium_ru_20_data;
    /* get font 'NS_Medium_ru_30' from a C array */
    NS_Medium_ru_30 = &NS_Medium_ru_30_data;
    /* get font 'NS_Medium_ru_40' from a C array */
    NS_Medium_ru_40 = &NS_Medium_ru_40_data;
    /* get font 'NS_Medium_el_14' from a C array */
    NS_Medium_el_14 = &NS_Medium_el_14_data;
    /* get font 'NS_Medium_el_16' from a C array */
    NS_Medium_el_16 = &NS_Medium_el_16_data;
    /* get font 'NS_Medium_el_18' from a C array */
    NS_Medium_el_18 = &NS_Medium_el_18_data;
    /* get font 'NS_Medium_el_20' from a C array */
    NS_Medium_el_20 = &NS_Medium_el_20_data;
    /* get font 'NS_Medium_el_30' from a C array */
    NS_Medium_el_30 = &NS_Medium_el_30_data;
    /* get font 'NS_Medium_el_40' from a C array */
    NS_Medium_el_40 = &NS_Medium_el_40_data;
    /* get font 'NS_Medium_hi_14' from a C array */
    NS_Medium_hi_14 = &NS_Medium_hi_14_data;
    /* get font 'NS_Medium_hi_16' from a C array */
    NS_Medium_hi_16 = &NS_Medium_hi_16_data;
    /* get font 'NS_Medium_hi_18' from a C array */
    NS_Medium_hi_18 = &NS_Medium_hi_18_data;
    /* get font 'NS_Medium_hi_20' from a C array */
    NS_Medium_hi_20 = &NS_Medium_hi_20_data;
    /* get font 'NS_Medium_hi_30' from a C array */
    NS_Medium_hi_30 = &NS_Medium_hi_30_data;
    /* get font 'NS_Medium_hi_40' from a C array */
    NS_Medium_hi_40 = &NS_Medium_hi_40_data;
    /* get font 'NS_Medium_th_14' from a C array */
    NS_Medium_th_14 = &NS_Medium_th_14_data;
    /* get font 'NS_Medium_th_16' from a C array */
    NS_Medium_th_16 = &NS_Medium_th_16_data;
    /* get font 'NS_Medium_th_18' from a C array */
    NS_Medium_th_18 = &NS_Medium_th_18_data;
    /* get font 'NS_Medium_th_20' from a C array */
    NS_Medium_th_20 = &NS_Medium_th_20_data;
    /* get font 'NS_Medium_th_30' from a C array */
    NS_Medium_th_30 = &NS_Medium_th_30_data;
    /* get font 'NS_Medium_th_40' from a C array */
    NS_Medium_th_40 = &NS_Medium_th_40_data;
    /* get font 'NS_Medium_zh_14' from a C array */
    NS_Medium_zh_14 = &NS_Medium_zh_14_data;
    /* get font 'NS_Medium_zh_16' from a C array */
    NS_Medium_zh_16 = &NS_Medium_zh_16_data;
    /* get font 'NS_Medium_zh_18' from a C array */
    NS_Medium_zh_18 = &NS_Medium_zh_18_data;
    /* get font 'NS_Medium_zh_20' from a C array */
    NS_Medium_zh_20 = &NS_Medium_zh_20_data;
    /* get font 'NS_Medium_zh_30' from a C array */
    NS_Medium_zh_30 = &NS_Medium_zh_30_data;
    /* get font 'NS_Medium_zh_40' from a C array */
    NS_Medium_zh_40 = &NS_Medium_zh_40_data;
    /* get font 'NS_Medium_jp_14' from a C array */
    NS_Medium_jp_14 = &NS_Medium_jp_14_data;
    /* get font 'NS_Medium_jp_16' from a C array */
    NS_Medium_jp_16 = &NS_Medium_jp_16_data;
    /* get font 'NS_Medium_jp_18' from a C array */
    NS_Medium_jp_18 = &NS_Medium_jp_18_data;
    /* get font 'NS_Medium_jp_20' from a C array */
    NS_Medium_jp_20 = &NS_Medium_jp_20_data;
    /* get font 'NS_Medium_jp_30' from a C array */
    NS_Medium_jp_30 = &NS_Medium_jp_30_data;
    /* get font 'NS_Medium_jp_40' from a C array */
    NS_Medium_jp_40 = &NS_Medium_jp_40_data;


    /*----------------
     * Images
     *----------------*/
    icon_empty = &icon_empty_data;
    icon_wifi = &icon_wifi_data;
    icon_list = &icon_list_data;
    icon_brightness_full = &icon_brightness_full_data;
    icon_brightness_empty = &icon_brightness_empty_data;
    icon_volume_high = &icon_volume_high_data;
    icon_volume_low = &icon_volume_low_data;
    icon_mute = &icon_mute_data;
    icon_play = &icon_play_data;
    icon_back = &icon_back_data;
    icon_next = &icon_next_data;
    icon_connect = &icon_connect_data;
    icon_vibration = &icon_vibration_data;
    icon_dnd = &icon_dnd_data;
    icon_qr = &icon_qr_data;
    icon_arrow_up = &icon_arrow_up_data;
    icon_settings_harddisk = &icon_settings_harddisk_data;
    icon_settings_brightness = &icon_settings_brightness_data;
    icon_settings_monitor = &icon_settings_monitor_data;
    icon_settings_information = &icon_settings_information_data;
    icon_settings_smartwatch = &icon_settings_smartwatch_data;
    icon_settings_rotate = &icon_settings_rotate_data;
    icon_settings_power = &icon_settings_power_data;
    icon_settings_bell = &icon_settings_bell_data;
    icon_application = &icon_application_data;
    icon_chat = &icon_chat_data;
    icon_weather = &icon_weather_data;
    icon_gear = &icon_gear_data;
    icon_measurement = &icon_measurement_data;
    icon_stopwatch = &icon_stopwatch_data;
    icon_contacts = &icon_contacts_data;
    icon_navigation = &icon_navigation_data;
    icon_timer = &icon_timer_data;
    icon_music = &icon_music_data;
    icon_folder = &icon_folder_data;
    icon_running = &icon_running_data;
    icon_sleep = &icon_sleep_data;
    icon_weather_humidity_icon = &icon_weather_humidity_icon_data;
    icon_weather_temp_up_icon = &icon_weather_temp_up_icon_data;
    icon_weather_temp_down_icon = &icon_weather_temp_down_icon_data;
    icon_weather_uv_icon = &icon_weather_uv_icon_data;

    /*----------------
     * Global styles
     *----------------*/

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_dark);
        lv_style_set_bg_color(&style_dark, lv_color_hex(0x000000));
        lv_style_set_text_color(&style_dark, lv_color_hex(0xffffff));

        lv_style_init(&style_primary_bg);
        lv_style_set_bg_color(&style_primary_bg, COLOR_PRIMARY);

        lv_style_init(&style_white_bg);
        lv_style_set_bg_color(&style_white_bg, lv_color_hex(0xffffff));

        lv_style_init(&style_icon_recolor);

        lv_style_init(&style_text_small_466);
        lv_style_set_text_font(&style_text_small_466, NS_Medium_20);

        lv_style_init(&style_text_small_360);
        lv_style_set_text_font(&style_text_small_360, NS_Medium_18);

        lv_style_init(&style_text_small_240);
        lv_style_set_text_font(&style_text_small_240, NS_Medium_14);

        lv_style_init(&style_text_normal_466);
        lv_style_set_text_font(&style_text_normal_466, NS_Medium_40);

        lv_style_init(&style_text_normal_360);
        lv_style_set_text_font(&style_text_normal_360, NS_Medium_30);

        lv_style_init(&style_text_normal_240);
        lv_style_set_text_font(&style_text_normal_240, NS_Medium_20);

        lv_style_init(&style_text_large_466);
        lv_style_set_text_font(&style_text_large_466, NS_Medium_140);

        lv_style_init(&style_text_large_360);
        lv_style_set_text_font(&style_text_large_360, NS_Medium_100);

        lv_style_init(&style_text_large_240);
        lv_style_set_text_font(&style_text_large_240, NS_Medium_70);

        style_inited = true;
    }

    /*----------------
     * Subjects
     *----------------*/
    lv_subject_init_int(&sb_screen_size, 0);
    lv_subject_init_int(&sb_screen_type, 0);
    lv_subject_init_int(&sb_app_list_mode, 0);
    lv_subject_set_min_value_int(&sb_app_list_mode, 0);
    lv_subject_set_max_value_int(&sb_app_list_mode, 1);
    lv_subject_init_int(&sb_list_circular_mode, 1);
    lv_subject_set_min_value_int(&sb_list_circular_mode, 0);
    lv_subject_set_max_value_int(&sb_list_circular_mode, 1);
    lv_subject_init_int(&sb_screen_brightness, 80);
    lv_subject_set_min_value_int(&sb_screen_brightness, 1);
    lv_subject_set_max_value_int(&sb_screen_brightness, 100);
    lv_subject_init_int(&sb_screen_rotation, 0);
    lv_subject_set_min_value_int(&sb_screen_rotation, 0);
    lv_subject_set_max_value_int(&sb_screen_rotation, 3);
    lv_subject_init_int(&sb_screen_timeout, 0);
    lv_subject_set_min_value_int(&sb_screen_timeout, 0);
    lv_subject_set_max_value_int(&sb_screen_timeout, 4);
    lv_subject_init_int(&sb_screen_rtw, 1);
    lv_subject_set_min_value_int(&sb_screen_rtw, 0);
    lv_subject_set_max_value_int(&sb_screen_rtw, 1);
    lv_subject_init_int(&sb_language, 0);
    lv_subject_init_int(&sb_battery_percent, 70);
    lv_subject_set_min_value_int(&sb_battery_percent, 0);
    lv_subject_set_max_value_int(&sb_battery_percent, 100);
    lv_subject_init_int(&sb_sound_volume, 40);
    lv_subject_set_min_value_int(&sb_sound_volume, 0);
    lv_subject_set_max_value_int(&sb_sound_volume, 100);
    lv_subject_init_int(&sb_focusable, 1);
    lv_subject_set_min_value_int(&sb_focusable, 0);
    lv_subject_set_max_value_int(&sb_focusable, 1);

    /*----------------
     * Translations
     *----------------*/

    #ifndef LV_EDITOR_PREVIEW
        lv_translation_add_static(translation_languages, translation_tags, translation_texts);
    #endif

#if LV_USE_XML
    /* Register widgets */
    wd_arcoiris_register();
    wd_dropdown_register();
    wd_image_register();
    wd_list_register();
    wd_segment_register();

    /* Register fonts */
    lv_xml_register_font(NULL, "NS_Medium_14", NS_Medium_14);
    lv_xml_register_font(NULL, "NS_Medium_16", NS_Medium_16);
    lv_xml_register_font(NULL, "NS_Medium_18", NS_Medium_18);
    lv_xml_register_font(NULL, "NS_Medium_20", NS_Medium_20);
    lv_xml_register_font(NULL, "NS_Medium_30", NS_Medium_30);
    lv_xml_register_font(NULL, "NS_Medium_40", NS_Medium_40);
    lv_xml_register_font(NULL, "NS_Medium_70", NS_Medium_70);
    lv_xml_register_font(NULL, "NS_Medium_100", NS_Medium_100);
    lv_xml_register_font(NULL, "NS_Medium_140", NS_Medium_140);
    lv_xml_register_font(NULL, "NS_Medium_latin_14", NS_Medium_latin_14);
    lv_xml_register_font(NULL, "NS_Medium_latin_16", NS_Medium_latin_16);
    lv_xml_register_font(NULL, "NS_Medium_latin_18", NS_Medium_latin_18);
    lv_xml_register_font(NULL, "NS_Medium_latin_20", NS_Medium_latin_20);
    lv_xml_register_font(NULL, "NS_Medium_latin_30", NS_Medium_latin_30);
    lv_xml_register_font(NULL, "NS_Medium_latin_40", NS_Medium_latin_40);
    lv_xml_register_font(NULL, "NS_Medium_ru_14", NS_Medium_ru_14);
    lv_xml_register_font(NULL, "NS_Medium_ru_16", NS_Medium_ru_16);
    lv_xml_register_font(NULL, "NS_Medium_ru_18", NS_Medium_ru_18);
    lv_xml_register_font(NULL, "NS_Medium_ru_20", NS_Medium_ru_20);
    lv_xml_register_font(NULL, "NS_Medium_ru_30", NS_Medium_ru_30);
    lv_xml_register_font(NULL, "NS_Medium_ru_40", NS_Medium_ru_40);
    lv_xml_register_font(NULL, "NS_Medium_el_14", NS_Medium_el_14);
    lv_xml_register_font(NULL, "NS_Medium_el_16", NS_Medium_el_16);
    lv_xml_register_font(NULL, "NS_Medium_el_18", NS_Medium_el_18);
    lv_xml_register_font(NULL, "NS_Medium_el_20", NS_Medium_el_20);
    lv_xml_register_font(NULL, "NS_Medium_el_30", NS_Medium_el_30);
    lv_xml_register_font(NULL, "NS_Medium_el_40", NS_Medium_el_40);
    lv_xml_register_font(NULL, "NS_Medium_hi_14", NS_Medium_hi_14);
    lv_xml_register_font(NULL, "NS_Medium_hi_16", NS_Medium_hi_16);
    lv_xml_register_font(NULL, "NS_Medium_hi_18", NS_Medium_hi_18);
    lv_xml_register_font(NULL, "NS_Medium_hi_20", NS_Medium_hi_20);
    lv_xml_register_font(NULL, "NS_Medium_hi_30", NS_Medium_hi_30);
    lv_xml_register_font(NULL, "NS_Medium_hi_40", NS_Medium_hi_40);
    lv_xml_register_font(NULL, "NS_Medium_th_14", NS_Medium_th_14);
    lv_xml_register_font(NULL, "NS_Medium_th_16", NS_Medium_th_16);
    lv_xml_register_font(NULL, "NS_Medium_th_18", NS_Medium_th_18);
    lv_xml_register_font(NULL, "NS_Medium_th_20", NS_Medium_th_20);
    lv_xml_register_font(NULL, "NS_Medium_th_30", NS_Medium_th_30);
    lv_xml_register_font(NULL, "NS_Medium_th_40", NS_Medium_th_40);
    lv_xml_register_font(NULL, "NS_Medium_zh_14", NS_Medium_zh_14);
    lv_xml_register_font(NULL, "NS_Medium_zh_16", NS_Medium_zh_16);
    lv_xml_register_font(NULL, "NS_Medium_zh_18", NS_Medium_zh_18);
    lv_xml_register_font(NULL, "NS_Medium_zh_20", NS_Medium_zh_20);
    lv_xml_register_font(NULL, "NS_Medium_zh_30", NS_Medium_zh_30);
    lv_xml_register_font(NULL, "NS_Medium_zh_40", NS_Medium_zh_40);
    lv_xml_register_font(NULL, "NS_Medium_jp_14", NS_Medium_jp_14);
    lv_xml_register_font(NULL, "NS_Medium_jp_16", NS_Medium_jp_16);
    lv_xml_register_font(NULL, "NS_Medium_jp_18", NS_Medium_jp_18);
    lv_xml_register_font(NULL, "NS_Medium_jp_20", NS_Medium_jp_20);
    lv_xml_register_font(NULL, "NS_Medium_jp_30", NS_Medium_jp_30);
    lv_xml_register_font(NULL, "NS_Medium_jp_40", NS_Medium_jp_40);

    /* Register subjects */
    lv_xml_register_subject(NULL, "sb_screen_size", &sb_screen_size);
    lv_xml_register_subject(NULL, "sb_screen_type", &sb_screen_type);
    lv_xml_register_subject(NULL, "sb_app_list_mode", &sb_app_list_mode);
    lv_xml_register_subject(NULL, "sb_list_circular_mode", &sb_list_circular_mode);
    lv_xml_register_subject(NULL, "sb_screen_brightness", &sb_screen_brightness);
    lv_xml_register_subject(NULL, "sb_screen_rotation", &sb_screen_rotation);
    lv_xml_register_subject(NULL, "sb_screen_timeout", &sb_screen_timeout);
    lv_xml_register_subject(NULL, "sb_screen_rtw", &sb_screen_rtw);
    lv_xml_register_subject(NULL, "sb_language", &sb_language);
    lv_xml_register_subject(NULL, "sb_battery_percent", &sb_battery_percent);
    lv_xml_register_subject(NULL, "sb_sound_volume", &sb_sound_volume);
    lv_xml_register_subject(NULL, "sb_focusable", &sb_focusable);

    /* Register callbacks */
    lv_xml_register_event_cb(NULL, "on_hs_info_cb", on_hs_info_cb);
    lv_xml_register_event_cb(NULL, "on_notifications_clicked_cb", on_notifications_clicked_cb);
    lv_xml_register_event_cb(NULL, "on_settings_clicked_cb", on_settings_clicked_cb);
    lv_xml_register_event_cb(NULL, "on_weather_clicked_cb", on_weather_clicked_cb);
    lv_xml_register_event_cb(NULL, "on_simulator_event_cb", on_simulator_event_cb);
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
    lv_xml_register_image(NULL, "icon_empty", icon_empty);
    lv_xml_register_image(NULL, "icon_wifi", icon_wifi);
    lv_xml_register_image(NULL, "icon_list", icon_list);
    lv_xml_register_image(NULL, "icon_brightness_full", icon_brightness_full);
    lv_xml_register_image(NULL, "icon_brightness_empty", icon_brightness_empty);
    lv_xml_register_image(NULL, "icon_volume_high", icon_volume_high);
    lv_xml_register_image(NULL, "icon_volume_low", icon_volume_low);
    lv_xml_register_image(NULL, "icon_mute", icon_mute);
    lv_xml_register_image(NULL, "icon_play", icon_play);
    lv_xml_register_image(NULL, "icon_back", icon_back);
    lv_xml_register_image(NULL, "icon_next", icon_next);
    lv_xml_register_image(NULL, "icon_connect", icon_connect);
    lv_xml_register_image(NULL, "icon_vibration", icon_vibration);
    lv_xml_register_image(NULL, "icon_dnd", icon_dnd);
    lv_xml_register_image(NULL, "icon_qr", icon_qr);
    lv_xml_register_image(NULL, "icon_arrow_up", icon_arrow_up);
    lv_xml_register_image(NULL, "icon_settings_harddisk", icon_settings_harddisk);
    lv_xml_register_image(NULL, "icon_settings_brightness", icon_settings_brightness);
    lv_xml_register_image(NULL, "icon_settings_monitor", icon_settings_monitor);
    lv_xml_register_image(NULL, "icon_settings_information", icon_settings_information);
    lv_xml_register_image(NULL, "icon_settings_smartwatch", icon_settings_smartwatch);
    lv_xml_register_image(NULL, "icon_settings_rotate", icon_settings_rotate);
    lv_xml_register_image(NULL, "icon_settings_power", icon_settings_power);
    lv_xml_register_image(NULL, "icon_settings_bell", icon_settings_bell);
    lv_xml_register_image(NULL, "icon_application", icon_application);
    lv_xml_register_image(NULL, "icon_chat", icon_chat);
    lv_xml_register_image(NULL, "icon_weather", icon_weather);
    lv_xml_register_image(NULL, "icon_gear", icon_gear);
    lv_xml_register_image(NULL, "icon_measurement", icon_measurement);
    lv_xml_register_image(NULL, "icon_stopwatch", icon_stopwatch);
    lv_xml_register_image(NULL, "icon_contacts", icon_contacts);
    lv_xml_register_image(NULL, "icon_navigation", icon_navigation);
    lv_xml_register_image(NULL, "icon_timer", icon_timer);
    lv_xml_register_image(NULL, "icon_music", icon_music);
    lv_xml_register_image(NULL, "icon_folder", icon_folder);
    lv_xml_register_image(NULL, "icon_running", icon_running);
    lv_xml_register_image(NULL, "icon_sleep", icon_sleep);
    lv_xml_register_image(NULL, "icon_weather_humidity_icon", icon_weather_humidity_icon);
    lv_xml_register_image(NULL, "icon_weather_temp_up_icon", icon_weather_temp_up_icon);
    lv_xml_register_image(NULL, "icon_weather_temp_down_icon", icon_weather_temp_down_icon);
    lv_xml_register_image(NULL, "icon_weather_uv_icon", icon_weather_uv_icon);
#endif

#if LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manaully from XML using lv_xml_create() */
#endif
}

/* Callbacks */
#if defined(LV_EDITOR_PREVIEW)
void __attribute__((weak)) on_hs_info_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_hs_info_cb was called\n");
}
void __attribute__((weak)) on_notifications_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_notifications_clicked_cb was called\n");
}
void __attribute__((weak)) on_settings_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_settings_clicked_cb was called\n");
}
void __attribute__((weak)) on_weather_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_weather_clicked_cb was called\n");
}
void __attribute__((weak)) on_simulator_event_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_simulator_event_cb was called\n");
}
#endif

/**********************
 *   STATIC FUNCTIONS
 **********************/