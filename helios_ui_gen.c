/**
 * @file helios_ui_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "helios_ui_gen.h"

#if defined(LV_USE_XML) && LV_USE_XML
#include "widgets/wd_arcoiris/wd_arcoiris_private_gen.h"
#include "widgets/wd_dropdown/wd_dropdown_private_gen.h"
#include "widgets/wd_image/wd_image_private_gen.h"
#include "widgets/wd_label/wd_label_private_gen.h"
#include "widgets/wd_list/wd_list_private_gen.h"
#include "widgets/wd_obj/wd_obj_private_gen.h"
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

static void check_font(lv_font_t ** font, const char * name);

/**********************
 *  STATIC VARIABLES
 **********************/

static uint32_t helios_ui_target = HELIOS_UI_TARGET_ALL;

/*----------------
 * Translations
 *----------------*/

#ifndef LV_EDITOR_PREVIEW
    static const char * translation_languages[] = {"en", "pt", "de", "es", "fr", "hu", "ru", "el", "th", "zh", "ja", "hi", NULL};
    static const char * translation_tags[] = {"id", "locale", "sun", "mon", "tue", "wed", "thur", "fri", "sat", "jan", "feb", "mar", "apr", "jun", "jul", "aug", "sept", "oct", "nov", "dec", "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december", "contacts", "files", "fitness", "health", "music", "navigation", "notifications", "settings", "sleep", "stopwatch", "timer", "weather", "display", "system", "alerts", "battery", "about", "storage", "brightness", "timeout", "rotation", "raise_to_wake", "circular_scroll", "grid_mode", "language", "reboot", "shutdown", "factory_reset", "sound", "vibration", "wake_screen", "dnd", "voltage", "temperature", "usage", "format", "firmware", "hourly_forecast", "daily_forecast", "timeout_5", "timeout_10", "timeout_20", "timeout_30", "always_on", "updated_at", "cloudy", "ram", "psram", "flash", "type", "steps", "watchfaces", "sd_card", "clear_all", "no_notifications", "camera", "music_control", NULL};
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
        "Aug", "agosto", "August", "Ago", "août", "Augusztus", "Август", "Αυγ", "ส.ค.", "八月", "8月", "अगस्त", /* aug */
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
        "Rotation", "Rotação", "Drehung", "Rotación", "Rotation", "Forgás", "Вращение", "Περιστροφή", "การหมุน", "旋转", "回転", "घुमाएँ", /* rotation */
        "Raise to wake", "Levante para acordar", "Zum Aufwecken hochziehen", "Levantarse para despertar", "Lever pour réveiller", "Ébredés", "Поднимитесь, чтобы проснуться", "Σήκωσε για να ξυπνήσεις", "ยกขึ้นเพื่อปลุก", "起身唤醒", "起こすために持ち上げる", "जगाने के लिए उठाएँ", /* raise_to_wake */
        "Circular scroll", "Pergaminho circular", "Kreisförmige Schriftrolle", "Pergamino circular", "rouleau circulaire", "Kör alakú görgetés", "Круглый свиток", "Κυκλική κύλιση", "ม้วนกลม", "圆形卷轴", "円形スクロール", "वृत्ताकार स्क्रॉल", /* circular_scroll */
        "Grid mode", "Modo de grade", "Rastermodus", "Modo cuadrícula", "Mode grille", "Rács mód", "Режим сетки", "Λειτουργία πλέγματος", "โหมดตาราง", "网格模式", "グリッドモード", "ग्रिड मोड", /* grid_mode */
        "Language", "Linguagem", "Sprache", "Idioma", "Langue", "Nyelv", "Язык", "Γλώσσα", "ภาษา", "语言", "言語", "भाषा", /* language */
        "Reboot", "Reinício", "Neustart", "Reiniciar", "Redémarrage", "Újraindítás", "Перезагрузить", "Επανεκκίνηση", "รีบูต", "重启", "リブート", "रीबूट", /* reboot */
        "Shutdown", "Desligar", "Abschalten", "Cerrar", "Fermer", "Leállítás", "Неисправность", "Κλείσιμο", "ปิดระบบ", "关闭", "シャットダウン", "शट डाउन", /* shutdown */
        "Factory Reset", "Restauração de fábrica", "Werksreset", "Restablecimiento de fábrica", "Réinitialisation d'usine", "Gyári visszaállítás", "Сброс к заводским настройкам", "Επαναφορά εργοστασιακών ρυθμίσεων", "รีเซ็ตเป็นค่าจากโรงงาน", "恢复出厂设置", "工場出荷時設定にリセット", "नए यंत्र जैसी सेटिंग", /* factory_reset */
        "Sound", "Som", "Klang", "Sonido", "Son", "Hang", "Звук", "Ήχος", "เสียง", "声音", "音", "आवाज़", /* sound */
        "Vibration", "Vibração", "Vibration", "Vibración", "Vibration", "Rezgés", "Вибрация", "Δόνηση", "การสั่นสะเทือน", "振动", "振動", "कंपन", /* vibration */
        "Wake screen", "Tela de ativação", "Bildschirm aufwecken", "Pantalla de activación", "Écran de réveil", "Képernyő felébresztése", "Экран пробуждения", "Οθόνη αφύπνισης", "หน้าจอปลุก", "唤醒屏幕", "起動画面", "जाग्रत स्क्रीन", /* wake_screen */
        "DND Mode", "Modo Não Perturbe", "Nicht stören-Modus", "Modo No Molestar", "Mode Ne pas déranger", "DND mód", "Режим «Не беспокоить»", "Λειτουργία DND", "โหมดห้ามรบกวน", "勿扰模式", "おやすみモード", "डीएनडी मोड", /* dnd */
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
        "Updated at", "Atualizado em", "Aktualisiert am", "Actualizado en", "Mise à jour le", "Frissítve:", "Обновлено в", "Ενημερώθηκε στις", "อัปเดตเมื่อ", "更新于", "更新日時", "अपडेट किया गया", /* updated_at */
        "Cloudy", "Nublado", "Wolkig", "Nublado", "Nuageux", "Felhős", "Облачно", "Νεφελώδης", "เมฆมาก", "多云", "曇り", "बादलों से घिरा", /* cloudy */
        "RAM", "BATER", "RAM", "RAM", "BÉLIER", "RAM", "БАРАН", "ΕΜΒΟΛΟ", "แรม", "内存", "ラム", "टक्कर मारना", /* ram */
        "PSRAM", "PSRAM", "PSRAM", "PSRAM", "PSRAM", "PSRAM", "ПСРАМ", "PSRAM", "พีเอสแรม", "PSRAM", "PSRAM", "पीएसआरएएम", /* psram */
        "Flash", "Clarão", "Blitz", "Destello", "Éclair", "Vaku", "Вспышка", "Λάμψη", "แฟลช", "闪光", "フラッシュ", "चमक", /* flash */
        "Type", "Tipo", "Typ", "Tipo", "Taper", "Típus", "Тип", "Τύπος", "พิมพ์", "类型", "タイプ", "प्रकार", /* type */
        "Steps", "Passos", "Schritte", "Pasos", "Mesures", "Lépések", "Шаги", "Βήματα", "ขั้นตอน", "步骤", "手順", "चरण", /* steps */
        "Watchfaces", "Mostradores de relógio", "Zifferblätter", "Esferas de reloj", "Cadrans de montre", "Óraszámlapok", "Циферблаты", "Προσόψεις ρολογιού", "หน้าปัดนาฬิกา", "表盘", "ウォッチフェイス", "वॉचफेस", /* watchfaces */
        "SD Card", "Cartão SD", "SD-Karte", "Tarjeta SD", "Carte SD", "SD-kártya", "SD-карта", "Κάρτα SD", "การ์ด SD", "SD卡", "SDカード", "एसडी कार्ड", /* sd_card */
        "Clear All", "Limpar tudo", "Alles löschen", "Borrar todo", "Effacer tout", "Összes törlése", "Очистить все", "Εκκαθάριση όλων", "ล้างทั้งหมด", "全部清除", "すべてクリア", "सभी साफ करें", /* clear_all */
        "No notifications avaialble, check back later", "Nenhuma notificação disponível. Volte mais tarde.", "Es sind keine Benachrichtigungen verfügbar. Bitte versuchen Sie es später erneut.", "No hay notificaciones disponibles, vuelva a intentarlo más tarde.", "Aucune notification disponible, veuillez réessayer plus tard.", "Nincsenek elérhető értesítések, nézz vissza később", "Уведомления недоступны, зайдите позже.", "Δεν υπάρχουν διαθέσιμες ειδοποιήσεις, ελέγξτε ξανά αργότερα", "ไม่มีการแจ้งเตือนใดๆ โปรดตรวจสอบอีกครั้งในภายหลัง", "暂无通知，请稍后查看。", "通知はありません。後ほどご確認ください。", "कोई सूचना उपलब्ध नहीं है, कृपया बाद में दोबारा देखें।", /* no_notifications */
        "Camera", "Câmera", "Kamera", "Cámara", "Caméra", "Kamera", "Камера", "Κάμερα", "กล้อง", "相机", "カメラ", "कैमरा", /* camera */
        "Music Control", "Controle de música", "Musiksteuerung", "Control de música", "Contrôle de la musique", "Zenevezérlés", "Управление музыкой", "Έλεγχος μουσικής", "การควบคุมดนตรี", "音乐控制", "音楽コントロール", "संगीत नियंत्रण", /* music_control */
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

lv_font_t * NS_Medium_70;
extern lv_font_t NS_Medium_70_data;
lv_font_t * NS_Medium_100;
extern lv_font_t NS_Medium_100_data;
lv_font_t * NS_Medium_140;
extern lv_font_t NS_Medium_140_data;
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

/* Targets: any */
const void * icon_empty = NULL;
extern const void * icon_empty_data;
const void * icon_wifi = NULL;
extern const void * icon_wifi_data;
const void * icon_list = NULL;
extern const void * icon_list_data;
const void * icon_brightness_full = NULL;
extern const void * icon_brightness_full_data;
const void * icon_brightness_empty = NULL;
extern const void * icon_brightness_empty_data;
const void * icon_volume_high = NULL;
extern const void * icon_volume_high_data;
const void * icon_volume_low = NULL;
extern const void * icon_volume_low_data;
const void * icon_mute = NULL;
extern const void * icon_mute_data;
const void * icon_play = NULL;
extern const void * icon_play_data;
const void * icon_back = NULL;
extern const void * icon_back_data;
const void * icon_next = NULL;
extern const void * icon_next_data;
const void * icon_connect = NULL;
extern const void * icon_connect_data;
const void * icon_vibration = NULL;
extern const void * icon_vibration_data;
const void * icon_dnd = NULL;
extern const void * icon_dnd_data;
const void * icon_qr = NULL;
extern const void * icon_qr_data;
const void * icon_arrow_up = NULL;
extern const void * icon_arrow_up_data;
const void * icon_turn_left = NULL;
extern const void * icon_turn_left_data;
const void * icon_settings_harddisk = NULL;
extern const void * icon_settings_harddisk_data;
const void * icon_settings_brightness = NULL;
extern const void * icon_settings_brightness_data;
const void * icon_settings_monitor = NULL;
extern const void * icon_settings_monitor_data;
const void * icon_settings_information = NULL;
extern const void * icon_settings_information_data;
const void * icon_settings_smartwatch = NULL;
extern const void * icon_settings_smartwatch_data;
const void * icon_settings_rotate = NULL;
extern const void * icon_settings_rotate_data;
const void * icon_settings_power = NULL;
extern const void * icon_settings_power_data;
const void * icon_settings_bell = NULL;
extern const void * icon_settings_bell_data;
const void * icon_application = NULL;
extern const void * icon_application_data;
const void * icon_chat = NULL;
extern const void * icon_chat_data;
const void * icon_weather = NULL;
extern const void * icon_weather_data;
const void * icon_gear = NULL;
extern const void * icon_gear_data;
const void * icon_measurement = NULL;
extern const void * icon_measurement_data;
const void * icon_stopwatch = NULL;
extern const void * icon_stopwatch_data;
const void * icon_contacts = NULL;
extern const void * icon_contacts_data;
const void * icon_navigation = NULL;
extern const void * icon_navigation_data;
const void * icon_timer = NULL;
extern const void * icon_timer_data;
const void * icon_music = NULL;
extern const void * icon_music_data;
const void * icon_folder = NULL;
extern const void * icon_folder_data;
const void * icon_running = NULL;
extern const void * icon_running_data;
const void * icon_sleep = NULL;
extern const void * icon_sleep_data;
const void * icon_user = NULL;
extern const void * icon_user_data;
const void * icon_spotify = NULL;
extern const void * icon_spotify_data;
const void * icon_phone_link = NULL;
extern const void * icon_phone_link_data;
const void * icon_weather_humidity_icon = NULL;
extern const void * icon_weather_humidity_icon_data;
const void * icon_weather_temp_up_icon = NULL;
extern const void * icon_weather_temp_up_icon_data;
const void * icon_weather_temp_down_icon = NULL;
extern const void * icon_weather_temp_down_icon_data;
const void * icon_weather_uv_icon = NULL;
extern const void * icon_weather_uv_icon_data;
const void * img_music_album = NULL;
extern const void * img_music_album_data;
const void * icon_vol_down_32 = NULL;
extern const void * icon_vol_down_32_data;
const void * icon_vol_up_32 = NULL;
extern const void * icon_vol_up_32_data;
const void * icon_music_play_32 = NULL;
extern const void * icon_music_play_32_data;
const void * icon_music_pause_32 = NULL;
extern const void * icon_music_pause_32_data;
const void * icon_music_next_32 = NULL;
extern const void * icon_music_next_32_data;
const void * icon_music_previous_32 = NULL;
extern const void * icon_music_previous_32_data;
const void * icon_stop = NULL;
extern const void * icon_stop_data;
const void * icon_timer_cancel = NULL;
extern const void * icon_timer_cancel_data;
const void * icon_timer_start = NULL;
extern const void * icon_timer_start_data;
const void * icon_timer_pause = NULL;
extern const void * icon_timer_pause_data;
const void * icon_lap_time = NULL;
extern const void * icon_lap_time_data;
const void * icon_restart = NULL;
extern const void * icon_restart_data;

/*----------------
 * Global styles
 *----------------*/

lv_style_t style_dark;
lv_style_t style_primary_bg;
lv_style_t style_white_bg;
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
lv_subject_t sb_screen_width;
lv_subject_t sb_screen_height;
lv_subject_t sb_screen_res;
lv_subject_t sb_placeholder;
lv_subject_t sb_lvgl_version;
lv_subject_t sb_app_list_mode;
lv_subject_t sb_list_circular_mode;
lv_subject_t sb_screen_brightness;
lv_subject_t sb_screen_rotation;
lv_subject_t sb_screen_timeout;
lv_subject_t sb_screen_rtw;
lv_subject_t sb_language;
lv_subject_t sb_sound_volume;
lv_subject_t sb_focusable;
lv_subject_t sb_time_string;
lv_subject_t sb_date_string;
lv_subject_t sb_time_hour;
lv_subject_t sb_time_minute;
lv_subject_t sb_time_seconds;
lv_subject_t sb_time_hour_analog;
lv_subject_t sb_time_minute_analog;
lv_subject_t sb_time_seconds_analog;
lv_subject_t sb_time_am_pm;
lv_subject_t sb_time_day;
lv_subject_t sb_time_month;
lv_subject_t sb_time_year;
lv_subject_t sb_time_month_short;
lv_subject_t sb_time_month_long;
lv_subject_t sb_time_weekday;
lv_subject_t sb_time_weekday_short;
lv_subject_t sb_time_weekday_long;
lv_subject_t sb_system_connection;
lv_subject_t sb_chronos_esp_version;
lv_subject_t sb_chronos_app_version;
lv_subject_t sb_firmware_version;
lv_subject_t sb_board_oem;
lv_subject_t sb_board_name;
lv_subject_t sb_board_type;
lv_subject_t sb_board_mac;
lv_subject_t sb_board_ram;
lv_subject_t sb_board_psram;
lv_subject_t sb_board_flash;
lv_subject_t sb_display_type;
lv_subject_t sb_battery_percent;
lv_subject_t sb_battery_charging;
lv_subject_t sb_battery_voltage;
lv_subject_t sb_battery_temp;
lv_subject_t sb_battery_usage;
lv_subject_t sb_nav_icon;
lv_subject_t sb_nav_text;
lv_subject_t sb_nav_title;
lv_subject_t sb_nav_directions;
lv_subject_t sb_music_app;
lv_subject_t sb_music_track;
lv_subject_t sb_music_artist;
lv_subject_t sb_music_state;
lv_subject_t sb_music_state_icon;
lv_subject_t sb_music_icon;
lv_subject_t sb_music_package;
lv_subject_t sb_music_album_color;
lv_subject_t sb_weather_icon;
lv_subject_t sb_weather_temp;
lv_subject_t sb_weather_location;
lv_subject_t sb_weather_condition;
lv_subject_t sb_weather_update_time;
lv_subject_t sb_weather_temp_unit;
lv_subject_t sb_weather_humidity;
lv_subject_t sb_weather_uv;
lv_subject_t sb_weather_temp_high;
lv_subject_t sb_weather_temp_low;
lv_subject_t sb_stopwatch_state;
lv_subject_t sb_stopwatch_time;
lv_subject_t sb_stopwatch_button_start_state;
lv_subject_t sb_stopwatch_button_reset_state;
lv_subject_t sb_stopwatch_button_start_icon;
lv_subject_t sb_stopwatch_button_reset_icon;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void helios_ui_init_gen(const char * asset_path)
{

    /*----------------
     * Fonts
     *----------------*/

    /* Targets: any */

    #if HELIOS_UI_CHECK_COMPILE_TARGET(HELIOS_UI_TARGET_ALL)
    if (helios_ui_check_target(HELIOS_UI_TARGET_ALL)) {
        if (!NS_Medium_70) {
            /* NS_Medium_70 */
            /* get font 'NS_Medium_70' from a C array */
            NS_Medium_70 = &NS_Medium_70_data;

        }
        if (!NS_Medium_100) {
            /* NS_Medium_100 */
            /* get font 'NS_Medium_100' from a C array */
            NS_Medium_100 = &NS_Medium_100_data;

        }
        if (!NS_Medium_140) {
            /* NS_Medium_140 */
            /* get font 'NS_Medium_140' from a C array */
            NS_Medium_140 = &NS_Medium_140_data;

        }
        if (!NS_Medium_14) {
            /* NS_Medium_14 */
            /* get font 'NS_Medium_14' from a C array */
            NS_Medium_14 = &NS_Medium_14_data;

        }
        if (!NS_Medium_16) {
            /* NS_Medium_16 */
            /* get font 'NS_Medium_16' from a C array */
            NS_Medium_16 = &NS_Medium_16_data;

        }
        if (!NS_Medium_18) {
            /* NS_Medium_18 */
            /* get font 'NS_Medium_18' from a C array */
            NS_Medium_18 = &NS_Medium_18_data;

        }
        if (!NS_Medium_20) {
            /* NS_Medium_20 */
            /* get font 'NS_Medium_20' from a C array */
            NS_Medium_20 = &NS_Medium_20_data;

        }
        if (!NS_Medium_30) {
            /* NS_Medium_30 */
            /* get font 'NS_Medium_30' from a C array */
            NS_Medium_30 = &NS_Medium_30_data;

        }
        if (!NS_Medium_40) {
            /* NS_Medium_40 */
            /* get font 'NS_Medium_40' from a C array */
            NS_Medium_40 = &NS_Medium_40_data;

        }
        if (!NS_Medium_latin_14) {
            /* NS_Medium_latin_14 */
            /* get font 'NS_Medium_latin_14' from a C array */
            NS_Medium_latin_14 = &NS_Medium_latin_14_data;

        }
        if (!NS_Medium_latin_16) {
            /* NS_Medium_latin_16 */
            /* get font 'NS_Medium_latin_16' from a C array */
            NS_Medium_latin_16 = &NS_Medium_latin_16_data;

        }
        if (!NS_Medium_latin_18) {
            /* NS_Medium_latin_18 */
            /* get font 'NS_Medium_latin_18' from a C array */
            NS_Medium_latin_18 = &NS_Medium_latin_18_data;

        }
        if (!NS_Medium_latin_20) {
            /* NS_Medium_latin_20 */
            /* get font 'NS_Medium_latin_20' from a C array */
            NS_Medium_latin_20 = &NS_Medium_latin_20_data;

        }
        if (!NS_Medium_latin_30) {
            /* NS_Medium_latin_30 */
            /* get font 'NS_Medium_latin_30' from a C array */
            NS_Medium_latin_30 = &NS_Medium_latin_30_data;

        }
        if (!NS_Medium_latin_40) {
            /* NS_Medium_latin_40 */
            /* get font 'NS_Medium_latin_40' from a C array */
            NS_Medium_latin_40 = &NS_Medium_latin_40_data;

        }
        if (!NS_Medium_ru_14) {
            /* NS_Medium_ru_14 */
            /* get font 'NS_Medium_ru_14' from a C array */
            NS_Medium_ru_14 = &NS_Medium_ru_14_data;

        }
        if (!NS_Medium_ru_16) {
            /* NS_Medium_ru_16 */
            /* get font 'NS_Medium_ru_16' from a C array */
            NS_Medium_ru_16 = &NS_Medium_ru_16_data;

        }
        if (!NS_Medium_ru_18) {
            /* NS_Medium_ru_18 */
            /* get font 'NS_Medium_ru_18' from a C array */
            NS_Medium_ru_18 = &NS_Medium_ru_18_data;

        }
        if (!NS_Medium_ru_20) {
            /* NS_Medium_ru_20 */
            /* get font 'NS_Medium_ru_20' from a C array */
            NS_Medium_ru_20 = &NS_Medium_ru_20_data;

        }
        if (!NS_Medium_ru_30) {
            /* NS_Medium_ru_30 */
            /* get font 'NS_Medium_ru_30' from a C array */
            NS_Medium_ru_30 = &NS_Medium_ru_30_data;

        }
        if (!NS_Medium_ru_40) {
            /* NS_Medium_ru_40 */
            /* get font 'NS_Medium_ru_40' from a C array */
            NS_Medium_ru_40 = &NS_Medium_ru_40_data;

        }
        if (!NS_Medium_el_14) {
            /* NS_Medium_el_14 */
            /* get font 'NS_Medium_el_14' from a C array */
            NS_Medium_el_14 = &NS_Medium_el_14_data;

        }
        if (!NS_Medium_el_16) {
            /* NS_Medium_el_16 */
            /* get font 'NS_Medium_el_16' from a C array */
            NS_Medium_el_16 = &NS_Medium_el_16_data;

        }
        if (!NS_Medium_el_18) {
            /* NS_Medium_el_18 */
            /* get font 'NS_Medium_el_18' from a C array */
            NS_Medium_el_18 = &NS_Medium_el_18_data;

        }
        if (!NS_Medium_el_20) {
            /* NS_Medium_el_20 */
            /* get font 'NS_Medium_el_20' from a C array */
            NS_Medium_el_20 = &NS_Medium_el_20_data;

        }
        if (!NS_Medium_el_30) {
            /* NS_Medium_el_30 */
            /* get font 'NS_Medium_el_30' from a C array */
            NS_Medium_el_30 = &NS_Medium_el_30_data;

        }
        if (!NS_Medium_el_40) {
            /* NS_Medium_el_40 */
            /* get font 'NS_Medium_el_40' from a C array */
            NS_Medium_el_40 = &NS_Medium_el_40_data;

        }
        if (!NS_Medium_hi_14) {
            /* NS_Medium_hi_14 */
            /* get font 'NS_Medium_hi_14' from a C array */
            NS_Medium_hi_14 = &NS_Medium_hi_14_data;

        }
        if (!NS_Medium_hi_16) {
            /* NS_Medium_hi_16 */
            /* get font 'NS_Medium_hi_16' from a C array */
            NS_Medium_hi_16 = &NS_Medium_hi_16_data;

        }
        if (!NS_Medium_hi_18) {
            /* NS_Medium_hi_18 */
            /* get font 'NS_Medium_hi_18' from a C array */
            NS_Medium_hi_18 = &NS_Medium_hi_18_data;

        }
        if (!NS_Medium_hi_20) {
            /* NS_Medium_hi_20 */
            /* get font 'NS_Medium_hi_20' from a C array */
            NS_Medium_hi_20 = &NS_Medium_hi_20_data;

        }
        if (!NS_Medium_hi_30) {
            /* NS_Medium_hi_30 */
            /* get font 'NS_Medium_hi_30' from a C array */
            NS_Medium_hi_30 = &NS_Medium_hi_30_data;

        }
        if (!NS_Medium_hi_40) {
            /* NS_Medium_hi_40 */
            /* get font 'NS_Medium_hi_40' from a C array */
            NS_Medium_hi_40 = &NS_Medium_hi_40_data;

        }
        if (!NS_Medium_th_14) {
            /* NS_Medium_th_14 */
            /* get font 'NS_Medium_th_14' from a C array */
            NS_Medium_th_14 = &NS_Medium_th_14_data;

        }
        if (!NS_Medium_th_16) {
            /* NS_Medium_th_16 */
            /* get font 'NS_Medium_th_16' from a C array */
            NS_Medium_th_16 = &NS_Medium_th_16_data;

        }
        if (!NS_Medium_th_18) {
            /* NS_Medium_th_18 */
            /* get font 'NS_Medium_th_18' from a C array */
            NS_Medium_th_18 = &NS_Medium_th_18_data;

        }
        if (!NS_Medium_th_20) {
            /* NS_Medium_th_20 */
            /* get font 'NS_Medium_th_20' from a C array */
            NS_Medium_th_20 = &NS_Medium_th_20_data;

        }
        if (!NS_Medium_th_30) {
            /* NS_Medium_th_30 */
            /* get font 'NS_Medium_th_30' from a C array */
            NS_Medium_th_30 = &NS_Medium_th_30_data;

        }
        if (!NS_Medium_th_40) {
            /* NS_Medium_th_40 */
            /* get font 'NS_Medium_th_40' from a C array */
            NS_Medium_th_40 = &NS_Medium_th_40_data;

        }
        if (!NS_Medium_zh_14) {
            /* NS_Medium_zh_14 */
            /* get font 'NS_Medium_zh_14' from a C array */
            NS_Medium_zh_14 = &NS_Medium_zh_14_data;

        }
        if (!NS_Medium_zh_16) {
            /* NS_Medium_zh_16 */
            /* get font 'NS_Medium_zh_16' from a C array */
            NS_Medium_zh_16 = &NS_Medium_zh_16_data;

        }
        if (!NS_Medium_zh_18) {
            /* NS_Medium_zh_18 */
            /* get font 'NS_Medium_zh_18' from a C array */
            NS_Medium_zh_18 = &NS_Medium_zh_18_data;

        }
        if (!NS_Medium_zh_20) {
            /* NS_Medium_zh_20 */
            /* get font 'NS_Medium_zh_20' from a C array */
            NS_Medium_zh_20 = &NS_Medium_zh_20_data;

        }
        if (!NS_Medium_zh_30) {
            /* NS_Medium_zh_30 */
            /* get font 'NS_Medium_zh_30' from a C array */
            NS_Medium_zh_30 = &NS_Medium_zh_30_data;

        }
        if (!NS_Medium_zh_40) {
            /* NS_Medium_zh_40 */
            /* get font 'NS_Medium_zh_40' from a C array */
            NS_Medium_zh_40 = &NS_Medium_zh_40_data;

        }
        if (!NS_Medium_jp_14) {
            /* NS_Medium_jp_14 */
            /* get font 'NS_Medium_jp_14' from a C array */
            NS_Medium_jp_14 = &NS_Medium_jp_14_data;

        }
        if (!NS_Medium_jp_16) {
            /* NS_Medium_jp_16 */
            /* get font 'NS_Medium_jp_16' from a C array */
            NS_Medium_jp_16 = &NS_Medium_jp_16_data;

        }
        if (!NS_Medium_jp_18) {
            /* NS_Medium_jp_18 */
            /* get font 'NS_Medium_jp_18' from a C array */
            NS_Medium_jp_18 = &NS_Medium_jp_18_data;

        }
        if (!NS_Medium_jp_20) {
            /* NS_Medium_jp_20 */
            /* get font 'NS_Medium_jp_20' from a C array */
            NS_Medium_jp_20 = &NS_Medium_jp_20_data;

        }
        if (!NS_Medium_jp_30) {
            /* NS_Medium_jp_30 */
            /* get font 'NS_Medium_jp_30' from a C array */
            NS_Medium_jp_30 = &NS_Medium_jp_30_data;

        }
        if (!NS_Medium_jp_40) {
            /* NS_Medium_jp_40 */
            /* get font 'NS_Medium_jp_40' from a C array */
            NS_Medium_jp_40 = &NS_Medium_jp_40_data;

        }
    }
    #endif

    /*----------------
     * Images
     *----------------*/

    /* Targets: any */
    #if HELIOS_UI_CHECK_COMPILE_TARGET(HELIOS_UI_TARGET_ALL)
    if (helios_ui_check_target(HELIOS_UI_TARGET_ALL)) {
        /* icon_empty */
        if (!icon_empty) {
            icon_empty = &icon_empty_data;
        }
        /* icon_wifi */
        if (!icon_wifi) {
            icon_wifi = &icon_wifi_data;
        }
        /* icon_list */
        if (!icon_list) {
            icon_list = &icon_list_data;
        }
        /* icon_brightness_full */
        if (!icon_brightness_full) {
            icon_brightness_full = &icon_brightness_full_data;
        }
        /* icon_brightness_empty */
        if (!icon_brightness_empty) {
            icon_brightness_empty = &icon_brightness_empty_data;
        }
        /* icon_volume_high */
        if (!icon_volume_high) {
            icon_volume_high = &icon_volume_high_data;
        }
        /* icon_volume_low */
        if (!icon_volume_low) {
            icon_volume_low = &icon_volume_low_data;
        }
        /* icon_mute */
        if (!icon_mute) {
            icon_mute = &icon_mute_data;
        }
        /* icon_play */
        if (!icon_play) {
            icon_play = &icon_play_data;
        }
        /* icon_back */
        if (!icon_back) {
            icon_back = &icon_back_data;
        }
        /* icon_next */
        if (!icon_next) {
            icon_next = &icon_next_data;
        }
        /* icon_connect */
        if (!icon_connect) {
            icon_connect = &icon_connect_data;
        }
        /* icon_vibration */
        if (!icon_vibration) {
            icon_vibration = &icon_vibration_data;
        }
        /* icon_dnd */
        if (!icon_dnd) {
            icon_dnd = &icon_dnd_data;
        }
        /* icon_qr */
        if (!icon_qr) {
            icon_qr = &icon_qr_data;
        }
        /* icon_arrow_up */
        if (!icon_arrow_up) {
            icon_arrow_up = &icon_arrow_up_data;
        }
        /* icon_turn_left */
        if (!icon_turn_left) {
            icon_turn_left = &icon_turn_left_data;
        }
        /* icon_settings_harddisk */
        if (!icon_settings_harddisk) {
            icon_settings_harddisk = &icon_settings_harddisk_data;
        }
        /* icon_settings_brightness */
        if (!icon_settings_brightness) {
            icon_settings_brightness = &icon_settings_brightness_data;
        }
        /* icon_settings_monitor */
        if (!icon_settings_monitor) {
            icon_settings_monitor = &icon_settings_monitor_data;
        }
        /* icon_settings_information */
        if (!icon_settings_information) {
            icon_settings_information = &icon_settings_information_data;
        }
        /* icon_settings_smartwatch */
        if (!icon_settings_smartwatch) {
            icon_settings_smartwatch = &icon_settings_smartwatch_data;
        }
        /* icon_settings_rotate */
        if (!icon_settings_rotate) {
            icon_settings_rotate = &icon_settings_rotate_data;
        }
        /* icon_settings_power */
        if (!icon_settings_power) {
            icon_settings_power = &icon_settings_power_data;
        }
        /* icon_settings_bell */
        if (!icon_settings_bell) {
            icon_settings_bell = &icon_settings_bell_data;
        }
        /* icon_application */
        if (!icon_application) {
            icon_application = &icon_application_data;
        }
        /* icon_chat */
        if (!icon_chat) {
            icon_chat = &icon_chat_data;
        }
        /* icon_weather */
        if (!icon_weather) {
            icon_weather = &icon_weather_data;
        }
        /* icon_gear */
        if (!icon_gear) {
            icon_gear = &icon_gear_data;
        }
        /* icon_measurement */
        if (!icon_measurement) {
            icon_measurement = &icon_measurement_data;
        }
        /* icon_stopwatch */
        if (!icon_stopwatch) {
            icon_stopwatch = &icon_stopwatch_data;
        }
        /* icon_contacts */
        if (!icon_contacts) {
            icon_contacts = &icon_contacts_data;
        }
        /* icon_navigation */
        if (!icon_navigation) {
            icon_navigation = &icon_navigation_data;
        }
        /* icon_timer */
        if (!icon_timer) {
            icon_timer = &icon_timer_data;
        }
        /* icon_music */
        if (!icon_music) {
            icon_music = &icon_music_data;
        }
        /* icon_folder */
        if (!icon_folder) {
            icon_folder = &icon_folder_data;
        }
        /* icon_running */
        if (!icon_running) {
            icon_running = &icon_running_data;
        }
        /* icon_sleep */
        if (!icon_sleep) {
            icon_sleep = &icon_sleep_data;
        }
        /* icon_user */
        if (!icon_user) {
            icon_user = &icon_user_data;
        }
        /* icon_spotify */
        if (!icon_spotify) {
            icon_spotify = &icon_spotify_data;
        }
        /* icon_phone_link */
        if (!icon_phone_link) {
            icon_phone_link = &icon_phone_link_data;
        }
        /* icon_weather_humidity_icon */
        if (!icon_weather_humidity_icon) {
            icon_weather_humidity_icon = &icon_weather_humidity_icon_data;
        }
        /* icon_weather_temp_up_icon */
        if (!icon_weather_temp_up_icon) {
            icon_weather_temp_up_icon = &icon_weather_temp_up_icon_data;
        }
        /* icon_weather_temp_down_icon */
        if (!icon_weather_temp_down_icon) {
            icon_weather_temp_down_icon = &icon_weather_temp_down_icon_data;
        }
        /* icon_weather_uv_icon */
        if (!icon_weather_uv_icon) {
            icon_weather_uv_icon = &icon_weather_uv_icon_data;
        }
        /* img_music_album */
        if (!img_music_album) {
            img_music_album = &img_music_album_data;
        }
        /* icon_vol_down_32 */
        if (!icon_vol_down_32) {
            icon_vol_down_32 = &icon_vol_down_32_data;
        }
        /* icon_vol_up_32 */
        if (!icon_vol_up_32) {
            icon_vol_up_32 = &icon_vol_up_32_data;
        }
        /* icon_music_play_32 */
        if (!icon_music_play_32) {
            icon_music_play_32 = &icon_music_play_32_data;
        }
        /* icon_music_pause_32 */
        if (!icon_music_pause_32) {
            icon_music_pause_32 = &icon_music_pause_32_data;
        }
        /* icon_music_next_32 */
        if (!icon_music_next_32) {
            icon_music_next_32 = &icon_music_next_32_data;
        }
        /* icon_music_previous_32 */
        if (!icon_music_previous_32) {
            icon_music_previous_32 = &icon_music_previous_32_data;
        }
        /* icon_stop */
        if (!icon_stop) {
            icon_stop = &icon_stop_data;
        }
        /* icon_timer_cancel */
        if (!icon_timer_cancel) {
            icon_timer_cancel = &icon_timer_cancel_data;
        }
        /* icon_timer_start */
        if (!icon_timer_start) {
            icon_timer_start = &icon_timer_start_data;
        }
        /* icon_timer_pause */
        if (!icon_timer_pause) {
            icon_timer_pause = &icon_timer_pause_data;
        }
        /* icon_lap_time */
        if (!icon_lap_time) {
            icon_lap_time = &icon_lap_time_data;
        }
        /* icon_restart */
        if (!icon_restart) {
            icon_restart = &icon_restart_data;
        }
    }
    #endif

    /*----------------
     * Global styles
     *----------------*/

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&style_dark);
        lv_style_init(&style_primary_bg);
        lv_style_init(&style_white_bg);
        lv_style_init(&style_text_small_466);
        lv_style_init(&style_text_small_360);
        lv_style_init(&style_text_small_240);
        lv_style_init(&style_text_normal_466);
        lv_style_init(&style_text_normal_360);
        lv_style_init(&style_text_normal_240);
        lv_style_init(&style_text_large_466);
        lv_style_init(&style_text_large_360);
        lv_style_init(&style_text_large_240);

        lv_style_set_bg_color(&style_dark, lv_color_hex(0x000000));
        lv_style_set_text_color(&style_dark, lv_color_hex(0xffffff));
        lv_style_set_bg_color(&style_primary_bg, COLOR_PRIMARY);
        lv_style_set_bg_color(&style_white_bg, lv_color_hex(0xffffff));
        lv_style_set_text_font(&style_text_small_466, NS_Medium_20);
        lv_style_set_text_font(&style_text_small_360, NS_Medium_18);
        lv_style_set_text_font(&style_text_small_240, NS_Medium_14);
        lv_style_set_text_font(&style_text_normal_466, NS_Medium_40);
        lv_style_set_text_font(&style_text_normal_360, NS_Medium_30);
        lv_style_set_text_font(&style_text_normal_240, NS_Medium_20);
        lv_style_set_text_font(&style_text_large_466, NS_Medium_140);
        lv_style_set_text_font(&style_text_large_360, NS_Medium_100);
        lv_style_set_text_font(&style_text_large_240, NS_Medium_70);

        style_inited = true;
    }

    /*----------------
     * Subjects
     *----------------*/
    lv_subject_init_int(&sb_screen_size, 0);
    lv_subject_init_int(&sb_screen_type, 0);
    lv_subject_init_int(&sb_screen_width, 466);
    lv_subject_init_int(&sb_screen_height, 466);
    static char sb_screen_res_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_screen_res_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_screen_res,
                           sb_screen_res_buf,
                           sb_screen_res_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "466x466"
                          );
    static char sb_placeholder_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_placeholder_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_placeholder,
                           sb_placeholder_buf,
                           sb_placeholder_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           ""
                          );
    static char sb_lvgl_version_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_lvgl_version_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_lvgl_version,
                           sb_lvgl_version_buf,
                           sb_lvgl_version_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "v9.0.0"
                          );
    lv_subject_init_int(&sb_app_list_mode, 0);
    lv_subject_set_min_value_int(&sb_app_list_mode, 0);
    lv_subject_set_max_value_int(&sb_app_list_mode, 1);
    lv_subject_init_int(&sb_list_circular_mode, 1);
    lv_subject_set_min_value_int(&sb_list_circular_mode, 0);
    lv_subject_set_max_value_int(&sb_list_circular_mode, 1);
    lv_subject_init_int(&sb_screen_brightness, 100);
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
    lv_subject_init_int(&sb_sound_volume, 40);
    lv_subject_set_min_value_int(&sb_sound_volume, 0);
    lv_subject_set_max_value_int(&sb_sound_volume, 100);
    lv_subject_init_int(&sb_focusable, 1);
    lv_subject_set_min_value_int(&sb_focusable, 0);
    lv_subject_set_max_value_int(&sb_focusable, 1);
    static char sb_time_string_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_time_string_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_time_string,
                           sb_time_string_buf,
                           sb_time_string_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "12:45"
                          );
    static char sb_date_string_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_date_string_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_date_string,
                           sb_date_string_buf,
                           sb_date_string_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "Sun 5 Oct"
                          );
    lv_subject_init_int(&sb_time_hour, 12);
    lv_subject_init_int(&sb_time_minute, 45);
    lv_subject_init_int(&sb_time_seconds, 23);
    lv_subject_init_int(&sb_time_hour_analog, 3150);
    lv_subject_init_int(&sb_time_minute_analog, 450);
    lv_subject_init_int(&sb_time_seconds_analog, 1800);
    static char sb_time_am_pm_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_time_am_pm_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_time_am_pm,
                           sb_time_am_pm_buf,
                           sb_time_am_pm_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "am"
                          );
    lv_subject_init_int(&sb_time_day, 5);
    lv_subject_init_int(&sb_time_month, 10);
    lv_subject_init_int(&sb_time_year, 2025);
    static char sb_time_month_short_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_time_month_short_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_time_month_short,
                           sb_time_month_short_buf,
                           sb_time_month_short_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "oct"
                          );
    static char sb_time_month_long_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_time_month_long_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_time_month_long,
                           sb_time_month_long_buf,
                           sb_time_month_long_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "october"
                          );
    lv_subject_init_int(&sb_time_weekday, 0);
    static char sb_time_weekday_short_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_time_weekday_short_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_time_weekday_short,
                           sb_time_weekday_short_buf,
                           sb_time_weekday_short_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "sun"
                          );
    static char sb_time_weekday_long_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_time_weekday_long_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_time_weekday_long,
                           sb_time_weekday_long_buf,
                           sb_time_weekday_long_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "sunday"
                          );
    lv_subject_init_int(&sb_system_connection, 0);
    static char sb_chronos_esp_version_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_chronos_esp_version_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_chronos_esp_version,
                           sb_chronos_esp_version_buf,
                           sb_chronos_esp_version_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "v1.9.0"
                          );
    static char sb_chronos_app_version_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_chronos_app_version_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_chronos_app_version,
                           sb_chronos_app_version_buf,
                           sb_chronos_app_version_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "v3.8.5"
                          );
    static char sb_firmware_version_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_firmware_version_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_firmware_version,
                           sb_firmware_version_buf,
                           sb_firmware_version_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "v1.0.0"
                          );
    static char sb_board_oem_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_board_oem_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_board_oem,
                           sb_board_oem_buf,
                           sb_board_oem_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "LVGL"
                          );
    static char sb_board_name_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_board_name_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_board_name,
                           sb_board_name_buf,
                           sb_board_name_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "Editor"
                          );
    static char sb_board_type_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_board_type_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_board_type,
                           sb_board_type_buf,
                           sb_board_type_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "ESP32-S3"
                          );
    static char sb_board_mac_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_board_mac_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_board_mac,
                           sb_board_mac_buf,
                           sb_board_mac_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "34:54:56:23:43:32"
                          );
    static char sb_board_ram_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_board_ram_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_board_ram,
                           sb_board_ram_buf,
                           sb_board_ram_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "384KB"
                          );
    static char sb_board_psram_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_board_psram_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_board_psram,
                           sb_board_psram_buf,
                           sb_board_psram_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "16MB"
                          );
    static char sb_board_flash_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_board_flash_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_board_flash,
                           sb_board_flash_buf,
                           sb_board_flash_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "16MB"
                          );
    static char sb_display_type_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_display_type_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_display_type,
                           sb_display_type_buf,
                           sb_display_type_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "AMOLED"
                          );
    lv_subject_init_int(&sb_battery_percent, 70);
    lv_subject_set_min_value_int(&sb_battery_percent, 0);
    lv_subject_set_max_value_int(&sb_battery_percent, 100);
    lv_subject_init_int(&sb_battery_charging, 0);
    lv_subject_set_min_value_int(&sb_battery_charging, 0);
    lv_subject_set_max_value_int(&sb_battery_charging, 1);
    lv_subject_init_float(&sb_battery_voltage, 3.92);
    lv_subject_init_float(&sb_battery_temp, 32.6);
    static char sb_battery_usage_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_battery_usage_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_battery_usage,
                           sb_battery_usage_buf,
                           sb_battery_usage_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "2d 14h"
                          );
    lv_subject_init_int(&sb_nav_icon, 0);
    static char sb_nav_text_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_nav_text_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_nav_text,
                           sb_nav_text_buf,
                           sb_nav_text_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "10:20 ETA\n5 mins | 1.6km"
                          );
    static char sb_nav_title_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_nav_title_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_nav_title,
                           sb_nav_title_buf,
                           sb_nav_title_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "100m"
                          );
    static char sb_nav_directions_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_nav_directions_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_nav_directions,
                           sb_nav_directions_buf,
                           sb_nav_directions_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "Turn left towards Kenyatta avenue at the round about"
                          );
    static char sb_music_app_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_music_app_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_music_app,
                           sb_music_app_buf,
                           sb_music_app_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "Music"
                          );
    static char sb_music_track_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_music_track_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_music_track,
                           sb_music_track_buf,
                           sb_music_track_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "Track"
                          );
    static char sb_music_artist_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_music_artist_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_music_artist,
                           sb_music_artist_buf,
                           sb_music_artist_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "Artist"
                          );
    lv_subject_init_int(&sb_music_state, 0);
    lv_subject_init_int(&sb_music_state_icon, 0);
    lv_subject_init_int(&sb_music_icon, 0);
    static char sb_music_package_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_music_package_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_music_package,
                           sb_music_package_buf,
                           sb_music_package_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "music"
                          );
    lv_subject_init_int(&sb_music_album_color, 0);
    lv_subject_init_int(&sb_weather_icon, 0);
    lv_subject_init_int(&sb_weather_temp, 23);
    static char sb_weather_location_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_weather_location_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_weather_location,
                           sb_weather_location_buf,
                           sb_weather_location_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "Nairobi"
                          );
    static char sb_weather_condition_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_weather_condition_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_weather_condition,
                           sb_weather_condition_buf,
                           sb_weather_condition_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "cloudy"
                          );
    static char sb_weather_update_time_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_weather_update_time_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_weather_update_time,
                           sb_weather_update_time_buf,
                           sb_weather_update_time_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "10:20"
                          );
    static char sb_weather_temp_unit_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_weather_temp_unit_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_weather_temp_unit,
                           sb_weather_temp_unit_buf,
                           sb_weather_temp_unit_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "C"
                          );
    lv_subject_init_int(&sb_weather_humidity, 45);
    lv_subject_init_int(&sb_weather_uv, 3);
    lv_subject_init_int(&sb_weather_temp_high, 30);
    lv_subject_init_int(&sb_weather_temp_low, 20);
    lv_subject_init_int(&sb_stopwatch_state, 0);
    static char sb_stopwatch_time_buf[UI_SUBJECT_STRING_LENGTH];
    static char sb_stopwatch_time_prev_buf[UI_SUBJECT_STRING_LENGTH];
    lv_subject_init_string(&sb_stopwatch_time,
                           sb_stopwatch_time_buf,
                           sb_stopwatch_time_prev_buf,
                           UI_SUBJECT_STRING_LENGTH,
                           "00:00:00"
                          );
    lv_subject_init_int(&sb_stopwatch_button_start_state, 0);
    lv_subject_init_int(&sb_stopwatch_button_reset_state, 0);
    lv_subject_init_int(&sb_stopwatch_button_start_icon, 0);
    lv_subject_init_int(&sb_stopwatch_button_reset_icon, 0);

    /*----------------
     * Translations
     *----------------*/

    #ifndef LV_EDITOR_PREVIEW
        lv_translation_add_static(translation_languages, translation_tags, translation_texts);
        lv_translation_set_language(translation_languages[0]);
    #endif

#if defined(LV_USE_XML) && LV_USE_XML
    /* Register widgets */
    wd_arcoiris_register();
    wd_dropdown_register();
    wd_image_register();
    wd_label_register();
    wd_list_register();
    wd_obj_register();
    wd_segment_register();

    /* Check all fonts / default if needed. This prevents fonts that are used in one target but
       defined in another from causing assertion failures during rendering of the Preview. */
    check_font(&NS_Medium_70, "NS_Medium_70");
    check_font(&NS_Medium_100, "NS_Medium_100");
    check_font(&NS_Medium_140, "NS_Medium_140");
    check_font(&NS_Medium_14, "NS_Medium_14");
    check_font(&NS_Medium_16, "NS_Medium_16");
    check_font(&NS_Medium_18, "NS_Medium_18");
    check_font(&NS_Medium_20, "NS_Medium_20");
    check_font(&NS_Medium_30, "NS_Medium_30");
    check_font(&NS_Medium_40, "NS_Medium_40");
    check_font(&NS_Medium_latin_14, "NS_Medium_latin_14");
    check_font(&NS_Medium_latin_16, "NS_Medium_latin_16");
    check_font(&NS_Medium_latin_18, "NS_Medium_latin_18");
    check_font(&NS_Medium_latin_20, "NS_Medium_latin_20");
    check_font(&NS_Medium_latin_30, "NS_Medium_latin_30");
    check_font(&NS_Medium_latin_40, "NS_Medium_latin_40");
    check_font(&NS_Medium_ru_14, "NS_Medium_ru_14");
    check_font(&NS_Medium_ru_16, "NS_Medium_ru_16");
    check_font(&NS_Medium_ru_18, "NS_Medium_ru_18");
    check_font(&NS_Medium_ru_20, "NS_Medium_ru_20");
    check_font(&NS_Medium_ru_30, "NS_Medium_ru_30");
    check_font(&NS_Medium_ru_40, "NS_Medium_ru_40");
    check_font(&NS_Medium_el_14, "NS_Medium_el_14");
    check_font(&NS_Medium_el_16, "NS_Medium_el_16");
    check_font(&NS_Medium_el_18, "NS_Medium_el_18");
    check_font(&NS_Medium_el_20, "NS_Medium_el_20");
    check_font(&NS_Medium_el_30, "NS_Medium_el_30");
    check_font(&NS_Medium_el_40, "NS_Medium_el_40");
    check_font(&NS_Medium_hi_14, "NS_Medium_hi_14");
    check_font(&NS_Medium_hi_16, "NS_Medium_hi_16");
    check_font(&NS_Medium_hi_18, "NS_Medium_hi_18");
    check_font(&NS_Medium_hi_20, "NS_Medium_hi_20");
    check_font(&NS_Medium_hi_30, "NS_Medium_hi_30");
    check_font(&NS_Medium_hi_40, "NS_Medium_hi_40");
    check_font(&NS_Medium_th_14, "NS_Medium_th_14");
    check_font(&NS_Medium_th_16, "NS_Medium_th_16");
    check_font(&NS_Medium_th_18, "NS_Medium_th_18");
    check_font(&NS_Medium_th_20, "NS_Medium_th_20");
    check_font(&NS_Medium_th_30, "NS_Medium_th_30");
    check_font(&NS_Medium_th_40, "NS_Medium_th_40");
    check_font(&NS_Medium_zh_14, "NS_Medium_zh_14");
    check_font(&NS_Medium_zh_16, "NS_Medium_zh_16");
    check_font(&NS_Medium_zh_18, "NS_Medium_zh_18");
    check_font(&NS_Medium_zh_20, "NS_Medium_zh_20");
    check_font(&NS_Medium_zh_30, "NS_Medium_zh_30");
    check_font(&NS_Medium_zh_40, "NS_Medium_zh_40");
    check_font(&NS_Medium_jp_14, "NS_Medium_jp_14");
    check_font(&NS_Medium_jp_16, "NS_Medium_jp_16");
    check_font(&NS_Medium_jp_18, "NS_Medium_jp_18");
    check_font(&NS_Medium_jp_20, "NS_Medium_jp_20");
    check_font(&NS_Medium_jp_30, "NS_Medium_jp_30");
    check_font(&NS_Medium_jp_40, "NS_Medium_jp_40");

    /* Register fonts */
    lv_xml_register_font(NULL, "NS_Medium_70", NS_Medium_70);
    lv_xml_register_font(NULL, "NS_Medium_100", NS_Medium_100);
    lv_xml_register_font(NULL, "NS_Medium_140", NS_Medium_140);
    lv_xml_register_font(NULL, "NS_Medium_14", NS_Medium_14);
    lv_xml_register_font(NULL, "NS_Medium_16", NS_Medium_16);
    lv_xml_register_font(NULL, "NS_Medium_18", NS_Medium_18);
    lv_xml_register_font(NULL, "NS_Medium_20", NS_Medium_20);
    lv_xml_register_font(NULL, "NS_Medium_30", NS_Medium_30);
    lv_xml_register_font(NULL, "NS_Medium_40", NS_Medium_40);
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
    lv_xml_register_subject(NULL, "sb_screen_width", &sb_screen_width);
    lv_xml_register_subject(NULL, "sb_screen_height", &sb_screen_height);
    lv_xml_register_subject(NULL, "sb_screen_res", &sb_screen_res);
    lv_xml_register_subject(NULL, "sb_placeholder", &sb_placeholder);
    lv_xml_register_subject(NULL, "sb_lvgl_version", &sb_lvgl_version);
    lv_xml_register_subject(NULL, "sb_app_list_mode", &sb_app_list_mode);
    lv_xml_register_subject(NULL, "sb_list_circular_mode", &sb_list_circular_mode);
    lv_xml_register_subject(NULL, "sb_screen_brightness", &sb_screen_brightness);
    lv_xml_register_subject(NULL, "sb_screen_rotation", &sb_screen_rotation);
    lv_xml_register_subject(NULL, "sb_screen_timeout", &sb_screen_timeout);
    lv_xml_register_subject(NULL, "sb_screen_rtw", &sb_screen_rtw);
    lv_xml_register_subject(NULL, "sb_language", &sb_language);
    lv_xml_register_subject(NULL, "sb_sound_volume", &sb_sound_volume);
    lv_xml_register_subject(NULL, "sb_focusable", &sb_focusable);
    lv_xml_register_subject(NULL, "sb_time_string", &sb_time_string);
    lv_xml_register_subject(NULL, "sb_date_string", &sb_date_string);
    lv_xml_register_subject(NULL, "sb_time_hour", &sb_time_hour);
    lv_xml_register_subject(NULL, "sb_time_minute", &sb_time_minute);
    lv_xml_register_subject(NULL, "sb_time_seconds", &sb_time_seconds);
    lv_xml_register_subject(NULL, "sb_time_hour_analog", &sb_time_hour_analog);
    lv_xml_register_subject(NULL, "sb_time_minute_analog", &sb_time_minute_analog);
    lv_xml_register_subject(NULL, "sb_time_seconds_analog", &sb_time_seconds_analog);
    lv_xml_register_subject(NULL, "sb_time_am_pm", &sb_time_am_pm);
    lv_xml_register_subject(NULL, "sb_time_day", &sb_time_day);
    lv_xml_register_subject(NULL, "sb_time_month", &sb_time_month);
    lv_xml_register_subject(NULL, "sb_time_year", &sb_time_year);
    lv_xml_register_subject(NULL, "sb_time_month_short", &sb_time_month_short);
    lv_xml_register_subject(NULL, "sb_time_month_long", &sb_time_month_long);
    lv_xml_register_subject(NULL, "sb_time_weekday", &sb_time_weekday);
    lv_xml_register_subject(NULL, "sb_time_weekday_short", &sb_time_weekday_short);
    lv_xml_register_subject(NULL, "sb_time_weekday_long", &sb_time_weekday_long);
    lv_xml_register_subject(NULL, "sb_system_connection", &sb_system_connection);
    lv_xml_register_subject(NULL, "sb_chronos_esp_version", &sb_chronos_esp_version);
    lv_xml_register_subject(NULL, "sb_chronos_app_version", &sb_chronos_app_version);
    lv_xml_register_subject(NULL, "sb_firmware_version", &sb_firmware_version);
    lv_xml_register_subject(NULL, "sb_board_oem", &sb_board_oem);
    lv_xml_register_subject(NULL, "sb_board_name", &sb_board_name);
    lv_xml_register_subject(NULL, "sb_board_type", &sb_board_type);
    lv_xml_register_subject(NULL, "sb_board_mac", &sb_board_mac);
    lv_xml_register_subject(NULL, "sb_board_ram", &sb_board_ram);
    lv_xml_register_subject(NULL, "sb_board_psram", &sb_board_psram);
    lv_xml_register_subject(NULL, "sb_board_flash", &sb_board_flash);
    lv_xml_register_subject(NULL, "sb_display_type", &sb_display_type);
    lv_xml_register_subject(NULL, "sb_battery_percent", &sb_battery_percent);
    lv_xml_register_subject(NULL, "sb_battery_charging", &sb_battery_charging);
    lv_xml_register_subject(NULL, "sb_battery_voltage", &sb_battery_voltage);
    lv_xml_register_subject(NULL, "sb_battery_temp", &sb_battery_temp);
    lv_xml_register_subject(NULL, "sb_battery_usage", &sb_battery_usage);
    lv_xml_register_subject(NULL, "sb_nav_icon", &sb_nav_icon);
    lv_xml_register_subject(NULL, "sb_nav_text", &sb_nav_text);
    lv_xml_register_subject(NULL, "sb_nav_title", &sb_nav_title);
    lv_xml_register_subject(NULL, "sb_nav_directions", &sb_nav_directions);
    lv_xml_register_subject(NULL, "sb_music_app", &sb_music_app);
    lv_xml_register_subject(NULL, "sb_music_track", &sb_music_track);
    lv_xml_register_subject(NULL, "sb_music_artist", &sb_music_artist);
    lv_xml_register_subject(NULL, "sb_music_state", &sb_music_state);
    lv_xml_register_subject(NULL, "sb_music_state_icon", &sb_music_state_icon);
    lv_xml_register_subject(NULL, "sb_music_icon", &sb_music_icon);
    lv_xml_register_subject(NULL, "sb_music_package", &sb_music_package);
    lv_xml_register_subject(NULL, "sb_music_album_color", &sb_music_album_color);
    lv_xml_register_subject(NULL, "sb_weather_icon", &sb_weather_icon);
    lv_xml_register_subject(NULL, "sb_weather_temp", &sb_weather_temp);
    lv_xml_register_subject(NULL, "sb_weather_location", &sb_weather_location);
    lv_xml_register_subject(NULL, "sb_weather_condition", &sb_weather_condition);
    lv_xml_register_subject(NULL, "sb_weather_update_time", &sb_weather_update_time);
    lv_xml_register_subject(NULL, "sb_weather_temp_unit", &sb_weather_temp_unit);
    lv_xml_register_subject(NULL, "sb_weather_humidity", &sb_weather_humidity);
    lv_xml_register_subject(NULL, "sb_weather_uv", &sb_weather_uv);
    lv_xml_register_subject(NULL, "sb_weather_temp_high", &sb_weather_temp_high);
    lv_xml_register_subject(NULL, "sb_weather_temp_low", &sb_weather_temp_low);
    lv_xml_register_subject(NULL, "sb_stopwatch_state", &sb_stopwatch_state);
    lv_xml_register_subject(NULL, "sb_stopwatch_time", &sb_stopwatch_time);
    lv_xml_register_subject(NULL, "sb_stopwatch_button_start_state", &sb_stopwatch_button_start_state);
    lv_xml_register_subject(NULL, "sb_stopwatch_button_reset_state", &sb_stopwatch_button_reset_state);
    lv_xml_register_subject(NULL, "sb_stopwatch_button_start_icon", &sb_stopwatch_button_start_icon);
    lv_xml_register_subject(NULL, "sb_stopwatch_button_reset_icon", &sb_stopwatch_button_reset_icon);

    /* Register callbacks */
    lv_xml_register_event_cb(NULL, "on_music_control_cb", on_music_control_cb);
    lv_xml_register_event_cb(NULL, "on_hs_info_cb", on_hs_info_cb);
    lv_xml_register_event_cb(NULL, "on_simulator_event_cb", on_simulator_event_cb);
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if defined(LV_USE_XML) && LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
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
    lv_xml_register_image(NULL, "icon_turn_left", icon_turn_left);
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
    lv_xml_register_image(NULL, "icon_user", icon_user);
    lv_xml_register_image(NULL, "icon_spotify", icon_spotify);
    lv_xml_register_image(NULL, "icon_phone_link", icon_phone_link);
    lv_xml_register_image(NULL, "icon_weather_humidity_icon", icon_weather_humidity_icon);
    lv_xml_register_image(NULL, "icon_weather_temp_up_icon", icon_weather_temp_up_icon);
    lv_xml_register_image(NULL, "icon_weather_temp_down_icon", icon_weather_temp_down_icon);
    lv_xml_register_image(NULL, "icon_weather_uv_icon", icon_weather_uv_icon);
    lv_xml_register_image(NULL, "img_music_album", img_music_album);
    lv_xml_register_image(NULL, "icon_vol_down_32", icon_vol_down_32);
    lv_xml_register_image(NULL, "icon_vol_up_32", icon_vol_up_32);
    lv_xml_register_image(NULL, "icon_music_play_32", icon_music_play_32);
    lv_xml_register_image(NULL, "icon_music_pause_32", icon_music_pause_32);
    lv_xml_register_image(NULL, "icon_music_next_32", icon_music_next_32);
    lv_xml_register_image(NULL, "icon_music_previous_32", icon_music_previous_32);
    lv_xml_register_image(NULL, "icon_stop", icon_stop);
    lv_xml_register_image(NULL, "icon_timer_cancel", icon_timer_cancel);
    lv_xml_register_image(NULL, "icon_timer_start", icon_timer_start);
    lv_xml_register_image(NULL, "icon_timer_pause", icon_timer_pause);
    lv_xml_register_image(NULL, "icon_lap_time", icon_lap_time);
    lv_xml_register_image(NULL, "icon_restart", icon_restart);
#endif

#if defined(LV_USE_XML) && LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manually from XML using lv_xml_create() */
#endif
}

void helios_ui_set_target(uint32_t target)
{
    helios_ui_target = target;
}

uint32_t helios_ui_get_target(void)
{
    return helios_ui_target;
}

bool helios_ui_check_target(uint32_t target)
{
    return (helios_ui_target & target) ? true : false;
}

/* Callbacks */
#if defined(LV_EDITOR_PREVIEW)
void __attribute__((weak)) on_music_control_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_music_control_cb was called\n");
}
void __attribute__((weak)) on_hs_info_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_hs_info_cb was called\n");
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

static void check_font(lv_font_t ** font, const char * name)
{
    if (!(*font)) {
        *font = (lv_font_t *)LV_FONT_DEFAULT;
        LV_LOG_WARN("font `%s` was not set. Using `LV_FONT_DEFAULT` instead", name);
    }
}