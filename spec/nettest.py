import jinja2
import json
import sys

class Documentation(object):
    def __init__(self, docs):
        self.docs = " ".join(docs.strip().replace("\n", " ").replace("\t", " ").split())

    def __str__(self):
        return self.docs

class Key(object):
    def __init__(self, name):
        self.name = name

    def __str__(self):
        return self.name

    def to_snake_case(self):
        return self.name.replace(".", "_").replace("/", "_")

    def to_snake_case_upper(self):
        return self.to_snake_case().upper()

    def to_pascal_case(self):
        name = self.to_snake_case()
        name = name.split("_")
        name = [elem.capitalize() for elem in name]
        return "".join(name)

    def to_camel_case(self):
        name = self.to_pascal_case()
        if len(name) > 0:
            name = name[0].lower() + name[1:]
        return name

class Type(object):
    def decl(self, language):
        raise NotImplementedError

    def default_value(self, language):
        raise NotImplementedError

    def to_json_cast(self, language):
        return ""

    def from_json_cast(self, language):
        return ""

class Bool(Type):
    def __init__(self, value=False):
        super().__init__()
        self._value = value

    def decl(self, language):
        return {
            "cxx": "double",
            "docs": "int",
        }[language]

    def default_value(self, language):
        return {
            "cxx": json.dumps(self._value),
            "docs": json.dumps(int(self._value)),
        }[language]

    def to_json_cast(self, language):
        return {
            "cxx": "(int64_t)",
        }[language]

    def from_json_cast(self, language):
        return {
            "cxx": "(bool)",
        }[language]

class Double(Type):
    def __init__(self, value=0.0):
        super().__init__()
        self._value = value

    def decl(self, language):
        return {
            "cxx": "double",
            "docs": "float",
        }[language]

    def default_value(self, language):
        return {
            "cxx": self._value,
            "docs": self._value,
        }[language]

class Int64(Type):
    def __init__(self, value=0):
        super().__init__()
        self._value = value

    def decl(self, language):
        return {
            "cxx": "int64_t",
            "docs": "int",
        }[language]

    def default_value(self, language):
        return {
            "cxx": self._value,
            "docs": self._value,
        }[language]

class String(Type):
    def __init__(self, value=""):
        super().__init__()
        self._value = str(value)

    def decl(self, language):
        return {
            "cxx": "std::string",
            "docs": "string",
        }[language]

    def default_value(self, language):
        return {
            "cxx": json.dumps(self._value),
            "docs": json.dumps(self._value),
        }[language]

class MapStringString(Type):
    def __init__(self):
        super().__init__()

    def decl(self, language):
        return {
            "cxx": "std::map<std::string, std::string>",
        }[language]

    def default_value(self, language):
        return {
            "cxx": "{}",
        }[language]

class VectorString(Type):
    def __init__(self):
        super().__init__()

    def decl(self, language):
        return {
            "cxx": "std::vector<std::string>",
        }[language]

    def default_value(self, language):
        return {
            "cxx": "{}",
        }[language]

class Attribute(object):
    def __init__(self, docs, base_type, key):
        self.docs = Documentation(docs)
        self.base_type = base_type
        self.key = Key(key)

class Event(object):
    def __init__(self, docs, key, *attributes):
        self.docs = Documentation(docs)
        self.key = Key(key)
        self.attributes = list(attributes)

class Nettest(object):
    def __init__(self, docs, key, reference_url, options=None):
        self.docs = Documentation(docs)
        self.key = Key(key)
        self.reference_url = reference_url
        self.options = options

class LogLevel(object):
    def __init__(self, docs, key):
        self.docs = Documentation(docs)
        self.key = Key(key)

def main():
    """ Main function """

    events = [Event("We could not lookup the ASN (Autonomous System Number) from the probe IP.",
                    "failure.asn_lookup",
                    Attribute(
                        "The specific error that occurred.",
                        String(), "failure")),
              Event("""Status update regarding the currently ongoing network
                       performance measurement. This event is, of course,
                       only emitted by network tests that measure the network
                       performance.""",
                    "status.update_performance",
                    Attribute(
                        """The direction of the performance measurement. Either
                           'download', for download measurements, or 'upload'
                           for upload measurements.""",
                        String(), "direction"),
                    Attribute(
                        """Seconds elapsed since the performance measurement
                           was started.""",
                        Double(), "elapsed"),
                    Attribute("Number of parallel TCP streams being used.",
                              Int64(), "num_streams"),
                    Attribute("Speed measured in kbit/s.",
                              Double(), "speed_kbps"))]

    options = [Attribute("""Base URL of the OONI bouncer. This base URL is
                            used to construct the full URL required to contact
                            the OONI bouncer and get test specific info like
                            test helpers and test collectors.""",
                         String("https://bouncer.ooni.io"), "bouncer_base_url"),
               Attribute("""Base URL of the OONI collector. This base URL is
                            used to construct the full URL required to contact
                            manage the report submission with the collector. By
                            default this option is not set because we use the
                            bouncer to retrieve the collector base URL.""",
                         String(""), "collector_base_url"),
               Attribute("""DNS resolver IP address. By setting this option
                            you will force MK to use that DNS resolver for
                            resolving domain names to IP addresses. For this
                            setting to work you should use a DNS engine
                            different from the "system" engine. By default
                            this option is not set, as we use the system engine
                            as our default DNS engine.""",
                         String(), "dns/nameserver"),
               Attribute("""What DNS engine to use. The "system" engine implies
                            that `getaddrinfo()` is used. If you set this
                            setting to "libevent" and you also configure the
                            "dns/nameserver" option, MK will use libevent
                            and the specified nameserver to resolve domain
                            names.""",
                         String("system"), "dns/engine"),
               Attribute("""Path to the GeoIP ASN (Autonomous System Number) database file. By default this
                            option is empty. If you do not change this option to
                            contain the path to a suitable database file, MK
                            will not be able to map the probe IP address to an
                            ASN.""",
                         String(), "geoip_asn_path"),
               Attribute("""Path to the GeoIP country database file. By default
                            this option is empty. If you do not change it to
                            contain the path to a suitable database file, MK will
                            not be able to map the probe IP to a country code.""",
                         String(), "geoip_country_path"),
               Attribute("""Whether to ignore bouncer errors. If this option
                            is true, then MK will not stop after failing to
                            contact the OONI bouncer. Without the information
                            provided by the bouncer, OONI tests that require
                            a test helper will certainly fail, while other tests
                            will just fail to submit their results to a
                            collector, unless you manually configure a collector
                            base URL.""",
                         Bool(True), "ignore_bouncer_error"),
               Attribute("""Whether to ignore errors opening the report with
                            the OONI collector.""",
                         Bool(True), "ignore_open_report_error"),
               Attribute("""Max run time for nettests taking input. When you
                            are running a nettest taking input, the test will
                            stop after the number of seconds specified by
                            this option has passed (plus some extra time required
                            to interrupt the testing engine). Setting this
                            option to a negative value lets the test run as
                            long as necessary to exhaust its input list.""",
                         Double(-1.0), "max_runtime"),
               Attribute("""Path to the CA used to validate SSL certificates. This
                            is not necessary where we use LibreSSL, because in
                            such cases we include a CA bundle directly inside of
                            the MK binary. This happens for Android, iOS, and
                            Windows systems. If this option is not set and
                            we're not using LibreSSL, then attempting to connect
                            to any website using HTTPS will fail.""",
                         String(), "net/ca_bundle_path"),
               Attribute("""Number of seconds after which network I/O
                            operations (i.e. connect, recv, send) will
                            timeout and return an error.""",
                         Double(10.0), "net/timeout"),
               Attribute("""Whether to avoid using a bouncer. Not using a
                            bouncer means we will not discover the base URL
                            of a suitable collector and of test helpers.
                            OONI tests that require test helpers will fail
                            if you disable the bouncer. Other tests will just not be
                            able to submit results to a collector, unless
                            you manually configure a collector base URL.""",
                         Bool(False), "no_bouncer"),
               Attribute("""Whether to avoid using a collector. If true, it means
                            that the test results are not submitted to a collector
                            (by default the OONI collector) for archival or
                            publishing purposes. All measurements submitted to
                            the OONI collector are published within a few
                            business days.""",
                         Bool(False), "no_collector"),
               Attribute("""Whether to avoid the the probe ASN (Autonomous System Number) lookup.""",
                         Bool(False), "no_asn_lookup"),
               Attribute("""Whether to avoid the probe country code lookup.""",
                         Bool(False), "no_cc_lookup"),
               Attribute("""Whether to avoid looking up the probe IP. Not knowing
                            it prevents us from looking up the ASN (Autonomous System Number)
                            and the country code. Most importantly, this also prevents us from
                            attempting to scrub the IP address from measurements results,
                            which may be a concern for censorship tests.""",
                         Bool(False), "no_ip_lookup"),
               Attribute("""Whether to avoid writing a report file to disk.""",
                         Bool(False), "no_file_report"),
               Attribute("""Whether to avoid looking up the resolver IP address.""",
                         Bool(False), "no_resolver_lookup"),
               Attribute("""The ASN (Autonomous System Number) in which we are. If you set this, we will
                            of course skip the probe ASN lookup.""",
                         String(), "probe_asn"),
               Attribute("""The country code in which we are. If you set this, we
                            will of course skip the probe country code lookup.""",
                         String(), "probe_cc"),
               Attribute("""The probe IP. If you set this, we will of course
                            skip the probe IP lookup.""",
                         String(), "probe_ip"),
               Attribute("""Whether to randomize the provided input.""",
                         Bool(True), "randomize_input"),
               Attribute("""Whether to save the probe ASN (Autonomous System Number) in the report.""",
                         Bool(True), "save_real_probe_asn"),
               Attribute("""Whether to save the probe country code in
                            the report.""",
                         Bool(True), "save_real_probe_cc"),
               Attribute("""Whether to save the probe IP in the report.""",
                         Bool(False), "save_real_probe_ip"),
               Attribute("""Whether to save the probe resolver IP in the report.""",
                         Bool(True), "save_real_resolver_ip"),
               Attribute("""Name of the application.""",
                         String("measurement_kit"), "software_name"),
               Attribute("""Version of the application. By default this is
                            an empty string. If you do not set this variable,
                            the current MK version will be used.""",
                         String(), "software_version")]

    settings = [Attribute("""Optional annotations (i.e. key, value string pairs)
                             that will be included into the JSON report sent to
                             the OONI collector.""",
                          MapStringString(), "annotations"),
                Attribute("""List of events that will not be emitted.""",
                          VectorString(), "disabled_events")]

    nettests = [Nettest("""Neubot's DASH test""", "dash",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-021-dash.md"),
                Nettest("""OONI's captive portal test""", "captive_portal",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-010-captive-portal.md"),
                Nettest("""OONI's DNS injection test""", "dns_injection",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-012-dns-injection.md"),
                Nettest("""OONI's Facebook Messenger test""", "facebook_messenger",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-019-facebook-messenger.md"),
                Nettest("""OONI's HTTP header field manipulation test""",
                        "http_header_field_manipulation",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-006-header-field-manipulation.md"),
                Nettest("""OONI's HTTP invalid request line test""",
                        "http_invalid_request_line",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-007-http-invalid-request-line.md"),
                Nettest("""OONI's meek fronted requests test""", "meek_fronted_requests",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-014-meek-fronted-requests.md"),
                Nettest("""the multi NDT network performance test""", "multi_ndt",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-022-ndt.md"),
                Nettest("""the NDT network performance test""", "ndt",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-022-ndt.md"),
                Nettest("""OONI's TCP connect test""", "tcp_connect",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-008-tcp-connect.md"),
                Nettest("""OONI's Telegram test""", "telegram",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-020-telegram.md"),
                Nettest("""OONI's Web Connectivity test""", "web_connectivity",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-017-web-connectivity.md"),
                Nettest("""OONI's WhatsApp test""", "whatsapp",
                        "https://github.com/ooni/spec/blob/master/test-specs/ts-018-whatsapp.md",
                        [Attribute(
                            """Whether to check all WhatsApp endpoints.""",
                            Bool(False), "all_endpoints",
                        )])]

    log_levels = [LogLevel("""Only emit error messages""", "err"),
                  LogLevel("""Also emit warning messages""", "warning"),
                  LogLevel("""Also emit informational messages""", "info"),
                  LogLevel("""Also emit debug messages""", "debug"),
                  LogLevel("""Emit all log messages""", "debug2")]

    for template_name in sys.argv[1:]:
        template = jinja2.Template(open(template_name, "r").read())
        render = template.render(events=events, options=options,
                                 settings=settings, nettests=nettests,
                                 log_levels=log_levels)
        print(render)

if __name__ == "__main__":
    main()
