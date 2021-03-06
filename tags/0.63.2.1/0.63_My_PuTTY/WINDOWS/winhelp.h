/*
 * winhelp.h - define Windows Help context names.
 * Each definition has the form "winhelp-topic:halibut-topic", where:
 *  - "winhelp-topic" matches up with the \cfg{winhelp-topic} directives
 *    in the Halibut source, and is used for WinHelp;
 *  - "halibut-topic" matches up with the Halibut keywords in the source,
 *    and is used for HTML Help.
 */

/* Maximum length for WINHELP_CTX_foo strings */
#define WINHELP_CTX_MAXLEN 80

/* These are used in the cross-platform configuration dialog code. */

#define HELPCTX(x) P(WINHELP_CTX_ ## x)

#define WINHELP_CTX_no_help NULL

#define WINHELP_CTX_session_hostname "session.hostname:config-hostname"
#define WINHELP_CTX_session_saved "session.saved:config-saving"
#define WINHELP_CTX_session_coe "session.coe:config-closeonexit"
#define WINHELP_CTX_logging_main "logging.main:config-logging"
#define WINHELP_CTX_logging_filename "logging.filename:config-logfilename"
#define WINHELP_CTX_logging_exists "logging.exists:config-logfileexists"
#define WINHELP_CTX_logging_flush "logging.flush:config-logflush"
#define WINHELP_CTX_logging_ssh_omit_password "logging.ssh.omitpassword:config-logssh"
#define WINHELP_CTX_logging_ssh_omit_data "logging.ssh.omitdata:config-logssh"
#define WINHELP_CTX_keyboard_backspace "keyboard.backspace:config-backspace"
#define WINHELP_CTX_keyboard_homeend "keyboard.homeend:config-homeend"
#define WINHELP_CTX_keyboard_funkeys "keyboard.funkeys:config-funkeys"
#define WINHELP_CTX_keyboard_appkeypad "keyboard.appkeypad:config-appkeypad"
#define WINHELP_CTX_keyboard_appcursor "keyboard.appcursor:config-appcursor"
#define WINHELP_CTX_keyboard_nethack "keyboard.nethack:config-nethack"
#define WINHELP_CTX_keyboard_compose "keyboard.compose:config-compose"
#define WINHELP_CTX_keyboard_ctrlalt "keyboard.ctrlalt:config-ctrlalt"
#define WINHELP_CTX_features_application "features.application:config-features-application"
#define WINHELP_CTX_features_mouse "features.mouse:config-features-mouse"
#define WINHELP_CTX_features_resize "features.resize:config-features-resize"
#define WINHELP_CTX_features_altscreen "features.altscreen:config-features-altscreen"
#define WINHELP_CTX_features_retitle "features.retitle:config-features-retitle"
#define WINHELP_CTX_features_qtitle "features.qtitle:config-features-qtitle"
#define WINHELP_CTX_features_dbackspace "features.dbackspace:config-features-dbackspace"
#define WINHELP_CTX_features_charset "features.charset:config-features-charset"
#define WINHELP_CTX_features_arabicshaping "features.arabicshaping:config-features-shaping"
#define WINHELP_CTX_features_bidi "features.bidi:config-features-bidi"
#define WINHELP_CTX_terminal_autowrap "terminal.autowrap:config-autowrap"
#define WINHELP_CTX_terminal_decom "terminal.decom:config-decom"
#define WINHELP_CTX_terminal_lfhascr "terminal.lfhascr:config-crlf"
#define WINHELP_CTX_terminal_crhaslf "terminal.crhaslf:config-lfcr"
#define WINHELP_CTX_terminal_bce "terminal.bce:config-erase"
#define WINHELP_CTX_terminal_blink "terminal.blink:config-blink"
#define WINHELP_CTX_terminal_answerback "terminal.answerback:config-answerback"
#define WINHELP_CTX_terminal_localecho "terminal.localecho:config-localecho"
#define WINHELP_CTX_terminal_localedit "terminal.localedit:config-localedit"
#define WINHELP_CTX_terminal_printing "terminal.printing:config-printing"
#define WINHELP_CTX_bell_style "bell.style:config-bellstyle"
#define WINHELP_CTX_bell_taskbar "bell.taskbar:config-belltaskbar"
#define WINHELP_CTX_bell_overload "bell.overload:config-bellovl"
#define WINHELP_CTX_window_size "window.size:config-winsize"
#define WINHELP_CTX_window_resize "window.resize:config-winsizelock"
#define WINHELP_CTX_window_scrollback "window.scrollback:config-scrollback"
#define WINHELP_CTX_window_erased "window.erased:config-erasetoscrollback"
#define WINHELP_CTX_behaviour_closewarn "behaviour.closewarn:config-warnonclose"
#define WINHELP_CTX_behaviour_altf4 "behaviour.altf4:config-altf4"
#define WINHELP_CTX_behaviour_altspace "behaviour.altspace:config-altspace"
#define WINHELP_CTX_behaviour_altonly "behaviour.altonly:config-altonly"
#define WINHELP_CTX_behaviour_alwaysontop "behaviour.alwaysontop:config-alwaysontop"
#define WINHELP_CTX_behaviour_altenter "behaviour.altenter:config-fullscreen"
#define WINHELP_CTX_appearance_cursor "appearance.cursor:config-cursor"
#define WINHELP_CTX_appearance_font "appearance.font:config-font"
#define WINHELP_CTX_appearance_title "appearance.title:config-title"
#define WINHELP_CTX_appearance_hidemouse "appearance.hidemouse:config-mouseptr"
#define WINHELP_CTX_appearance_border "appearance.border:config-winborder"
#define WINHELP_CTX_connection_termtype "connection.termtype:config-termtype"
#define WINHELP_CTX_connection_termspeed "connection.termspeed:config-termspeed"
#define WINHELP_CTX_connection_username "connection.username:config-username"
#define WINHELP_CTX_connection_username_from_env "connection.usernamefromenv:config-username-from-env"
#define WINHELP_CTX_connection_keepalive "connection.keepalive:config-keepalive"
#define WINHELP_CTX_connection_nodelay "connection.nodelay:config-nodelay"
#define WINHELP_CTX_connection_ipversion "connection.ipversion:config-address-family"
#define WINHELP_CTX_connection_tcpkeepalive "connection.tcpkeepalive:config-tcp-keepalives"
#define WINHELP_CTX_connection_loghost "connection.loghost:config-loghost"
#define WINHELP_CTX_proxy_type "proxy.type:config-proxy-type"
#define WINHELP_CTX_proxy_main "proxy.main:config-proxy"
#define WINHELP_CTX_proxy_exclude "proxy.exclude:config-proxy-exclude"
#define WINHELP_CTX_proxy_dns "proxy.dns:config-proxy-dns"
#define WINHELP_CTX_proxy_auth "proxy.auth:config-proxy-auth"
#define WINHELP_CTX_proxy_command "proxy.command:config-proxy-command"
#define WINHELP_CTX_telnet_environ "telnet.environ:config-environ"
#define WINHELP_CTX_telnet_oldenviron "telnet.oldenviron:config-oldenviron"
#define WINHELP_CTX_telnet_passive "telnet.passive:config-ptelnet"
#define WINHELP_CTX_telnet_specialkeys "telnet.specialkeys:config-telnetkey"
#define WINHELP_CTX_telnet_newline "telnet.newline:config-telnetnl"
#define WINHELP_CTX_rlogin_localuser "rlogin.localuser:config-rlogin-localuser"
#define WINHELP_CTX_ssh_nopty "ssh.nopty:config-ssh-pty"
#define WINHELP_CTX_ssh_ttymodes "ssh.ttymodes:config-ttymodes"
#define WINHELP_CTX_ssh_noshell "ssh.noshell:config-ssh-noshell"
#define WINHELP_CTX_ssh_ciphers "ssh.ciphers:config-ssh-encryption"
#define WINHELP_CTX_ssh_protocol "ssh.protocol:config-ssh-prot"
#define WINHELP_CTX_ssh_command "ssh.command:config-command"
#define WINHELP_CTX_ssh_compress "ssh.compress:config-ssh-comp"
#define WINHELP_CTX_ssh_kexlist "ssh.kex.order:config-ssh-kex-order"
#define WINHELP_CTX_ssh_kex_repeat "ssh.kex.repeat:config-ssh-kex-rekey"
#define WINHELP_CTX_ssh_auth_bypass "ssh.auth.bypass:config-ssh-noauth"
#define WINHELP_CTX_ssh_auth_banner "ssh.auth.banner:config-ssh-banner"
#define WINHELP_CTX_ssh_auth_privkey "ssh.auth.privkey:config-ssh-privkey"
#define WINHELP_CTX_ssh_auth_agentfwd "ssh.auth.agentfwd:config-ssh-agentfwd"
#define WINHELP_CTX_ssh_auth_changeuser "ssh.auth.changeuser:config-ssh-changeuser"
#define WINHELP_CTX_ssh_auth_pageant "ssh.auth.pageant:config-ssh-tryagent"
#define WINHELP_CTX_ssh_auth_tis "ssh.auth.tis:config-ssh-tis"
#define WINHELP_CTX_ssh_auth_ki "ssh.auth.ki:config-ssh-ki"
#define WINHELP_CTX_ssh_gssapi "ssh.auth.gssapi:config-ssh-auth-gssapi"
#define WINHELP_CTX_ssh_gssapi_delegation "ssh.auth.gssapi.delegation:config-ssh-auth-gssapi-delegation"
#define WINHELP_CTX_ssh_gssapi_libraries "ssh.auth.gssapi.libraries:config-ssh-auth-gssapi-libraries"
#define WINHELP_CTX_selection_buttons "selection.buttons:config-mouse"
#define WINHELP_CTX_selection_shiftdrag "selection.shiftdrag:config-mouseshift"
#define WINHELP_CTX_selection_rect "selection.rect:config-rectselect"
#define WINHELP_CTX_selection_charclasses "selection.charclasses:config-charclasses"
#define WINHELP_CTX_selection_linedraw "selection.linedraw:config-linedrawpaste"
#define WINHELP_CTX_selection_rtf "selection.rtf:config-rtfpaste"
#define WINHELP_CTX_colours_ansi "colours.ansi:config-ansicolour"
#define WINHELP_CTX_colours_xterm256 "colours.xterm256:config-xtermcolour"
#define WINHELP_CTX_colours_bold "colours.bold:config-boldcolour"
#define WINHELP_CTX_colours_system "colours.system:config-syscolour"
#define WINHELP_CTX_colours_logpal "colours.logpal:config-logpalette"
#define WINHELP_CTX_colours_config "colours.config:config-colourcfg"
#define WINHELP_CTX_translation_codepage "translation.codepage:config-charset"
#define WINHELP_CTX_translation_cjk_ambig_wide "translation.cjkambigwide:config-cjk-ambig-wide"
#define WINHELP_CTX_translation_cyrillic "translation.cyrillic:config-cyr"
#define WINHELP_CTX_translation_linedraw "translation.linedraw:config-linedraw"
#define WINHELP_CTX_ssh_tunnels_x11 "ssh.tunnels.x11:config-ssh-x11"
#define WINHELP_CTX_ssh_tunnels_x11auth "ssh.tunnels.x11auth:config-ssh-x11auth"
#define WINHELP_CTX_ssh_tunnels_xauthority "ssh.tunnels.xauthority:config-ssh-xauthority"
#define WINHELP_CTX_ssh_tunnels_portfwd "ssh.tunnels.portfwd:config-ssh-portfwd"
#define WINHELP_CTX_ssh_tunnels_portfwd_localhost "ssh.tunnels.portfwd.localhost:config-ssh-portfwd-localhost"
#define WINHELP_CTX_ssh_tunnels_portfwd_ipversion "ssh.tunnels.portfwd.ipversion:config-ssh-portfwd-address-family"
#define WINHELP_CTX_ssh_bugs_ignore1 "ssh.bugs.ignore1:config-ssh-bug-ignore1"
#define WINHELP_CTX_ssh_bugs_plainpw1 "ssh.bugs.plainpw1:config-ssh-bug-plainpw1"
#define WINHELP_CTX_ssh_bugs_rsa1 "ssh.bugs.rsa1:config-ssh-bug-rsa1"
#define WINHELP_CTX_ssh_bugs_ignore2 "ssh.bugs.ignore2:config-ssh-bug-ignore2"
#define WINHELP_CTX_ssh_bugs_hmac2 "ssh.bugs.hmac2:config-ssh-bug-hmac2"
#define WINHELP_CTX_ssh_bugs_derivekey2 "ssh.bugs.derivekey2:config-ssh-bug-derivekey2"
#define WINHELP_CTX_ssh_bugs_rsapad2 "ssh.bugs.rsapad2:config-ssh-bug-sig"
#define WINHELP_CTX_ssh_bugs_pksessid2 "ssh.bugs.pksessid2:config-ssh-bug-pksessid2"
#define WINHELP_CTX_ssh_bugs_rekey2 "ssh.bugs.rekey2:config-ssh-bug-rekey"
#define WINHELP_CTX_ssh_bugs_maxpkt2 "ssh.bugs.maxpkt2:config-ssh-bug-maxpkt2"
#define WINHELP_CTX_ssh_bugs_winadj "ssh.bugs.winadj:config-ssh-bug-winadj"
#define WINHELP_CTX_serial_line "serial.line:config-serial-line"
#define WINHELP_CTX_serial_speed "serial.speed:config-serial-speed"
#define WINHELP_CTX_serial_databits "serial.databits:config-serial-databits"
#define WINHELP_CTX_serial_stopbits "serial.stopbits:config-serial-stopbits"
#define WINHELP_CTX_serial_parity "serial.parity:config-serial-parity"
#define WINHELP_CTX_serial_flow "serial.flow:config-serial-flow"

#define WINHELP_CTX_pageant_general "pageant.general:pageant"
#define WINHELP_CTX_pageant_keylist "pageant.keylist:pageant-mainwin-keylist"
#define WINHELP_CTX_pageant_addkey "pageant.addkey:pageant-mainwin-addkey"
#define WINHELP_CTX_pageant_remkey "pageant.remkey:pageant-mainwin-remkey"
#define WINHELP_CTX_pgpfingerprints "pgpfingerprints:pgpkeys"
#define WINHELP_CTX_puttygen_general "puttygen.general:pubkey-puttygen"
#define WINHELP_CTX_puttygen_keytype "puttygen.keytype:puttygen-keytype"
#define WINHELP_CTX_puttygen_bits "puttygen.bits:puttygen-strength"
#define WINHELP_CTX_puttygen_generate "puttygen.generate:puttygen-generate"
#define WINHELP_CTX_puttygen_fingerprint "puttygen.fingerprint:puttygen-fingerprint"
#define WINHELP_CTX_puttygen_comment "puttygen.comment:puttygen-comment"
#define WINHELP_CTX_puttygen_passphrase "puttygen.passphrase:puttygen-passphrase"
#define WINHELP_CTX_puttygen_savepriv "puttygen.savepriv:puttygen-savepriv"
#define WINHELP_CTX_puttygen_savepub "puttygen.savepub:puttygen-savepub"
#define WINHELP_CTX_puttygen_pastekey "puttygen.pastekey:puttygen-pastekey"
#define WINHELP_CTX_puttygen_load "puttygen.load:puttygen-load"
#define WINHELP_CTX_puttygen_conversions "puttygen.conversions:puttygen-conversions"

/* These are used in Windows-specific bits of the frontend.
 * We (ab)use "help context identifiers" (dwContextId) to identify them. */

#define HELPCTXID(x) WINHELP_CTXID_ ## x

#define WINHELP_CTXID_no_help 0
#define WINHELP_CTX_errors_hostkey_absent "errors.hostkey.absent:errors-hostkey-absent"
#define WINHELP_CTXID_errors_hostkey_absent 1
#define WINHELP_CTX_errors_hostkey_changed "errors.hostkey.changed:errors-hostkey-wrong"
#define WINHELP_CTXID_errors_hostkey_changed 2
#define WINHELP_CTX_errors_cantloadkey "errors.cantloadkey:errors-cant-load-key"
#define WINHELP_CTXID_errors_cantloadkey 3
#define WINHELP_CTX_option_cleanup "options.cleanup:using-cleanup"
#define WINHELP_CTXID_option_cleanup 4
#define WINHELP_CTX_pgp_fingerprints "pgpfingerprints:pgpkeys"
#define WINHELP_CTXID_pgp_fingerprints 5

#ifdef PERSOPORT
#define WINHELP_CTX_behaviour_sendtotray "behaviour.sendtotray:config-sendtotray"
#define WINHELP_CTX_behaviour_maximize "behaviour.maximize:config-maximize"
#define WINHELP_CTX_behaviour_fullscreen "behaviour.fullscreen:config-fullscreen"
#define WINHELP_CTX_behaviour_saveonexit "behaviour.saveonexit:config-saveonexit"
#define WINHELP_CTX_session_folder "session.folder:config-folder"
#define WINHELP_CTX_appearance_icone "appearance.icone:config-icone"
#define WINHELP_CTX_appearance_iconefile "appearance.iconefile:config-iconefile"
#define WINHELP_CTX_connection_password "connection.password:config-password"
#define WINHELP_CTX_connection_autocommand "connection.autocommand:config-autocommand"
#define WINHELP_CTX_connection_antiidle "connection.antiidle:config-antiidle"
#define WINHELP_CTX_connection_class "connection.class:config-class"
#define WINHELP_CTX_scriptfile "connection.scriptfile:config-scriptfile"
#define WINHELP_CTX_logging_logtimestamp "connection.logging.logtimestamp"
#define WINHELP_CTX_bell_foregroundonbell "bell.foregroundonbell:config-foregroundonbell"
#endif

#if (defined IMAGEPORT) && (!defined FDJ)
#define WINHELP_CTX_appearance_background "appearance.background"
#endif

#ifdef RECONNECTPORT
#define WINHELP_CTX_connection_wakeup_reconnect "connection.wakeup_reconnect:config-wakeup_reconnect"
#define WINHELP_CTX_connection_failure_reconnect "connection.failure_reconnect:config-failure_reconnect"
#endif

#ifdef SCPORT
#define WINHELP_CTX_ssh_write_syslog "ssh.write.syslog"
#define WINHELP_CTX_ssh_auth_pkcs11 "ssh.auth.pkcs11"
#define WINHELP_CTX_ssh_auth_pkcs11_libfile "ssh.auth.pkcs11libfile"
#define WINHELP_CTX_ssh_auth_pkcs11_token_label "ssh.auth.pkcs11tokenlabel"
#define WINHELP_CTX_ssh_auth_pkcs11_cert_label "ssh.auth.pkcs11certlabel"
#endif

#ifdef ZMODEMPORT
#define WINHELP_CTX_zmodem_rzcommand "zmodem.rzcommand"
#define WINHELP_CTX_zmodem_rzoptions "zmodem.rzoptions"
#define WINHELP_CTX_zmodem_szcommand "zmodem.szcommand"
#define WINHELP_CTX_zmodem_szoptions "zmodem.szoptions"
#define WINHELP_CTX_zmodem_zdownloaddir "zmodem.zdownloaddir"
#endif
