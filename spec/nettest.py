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

    def to_snake_case(self):
        return self.name.replace(".", "_")

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

class Bool(Type):
    def __init__(self, value=False):
        super().__init__()
        self._value = value

    def decl(self, language):
        return {
            "cxx": "double",
        }[language]

    def default_value(self, language):
        return {
            "cxx": json.dumps(self._value),
        }[language]

class Double(Type):
    def __init__(self, value=0.0):
        super().__init__()
        self._value = value

    def decl(self, language):
        return {
            "cxx": "double",
        }[language]

    def default_value(self, language):
        return {
            "cxx": self._value,
        }[language]

class Int64(Type):
    def __init__(self, value=0):
        super().__init__()
        self._value = value

    def decl(self, language):
        return {
            "cxx": "int64_t",
        }[language]

    def default_value(self, language):
        return {
            "cxx": self._value
        }[language]

class String(Type):
    def __init__(self, value=""):
        super().__init__()
        self._value = str(value)

    def decl(self, language):
        return {
            "cxx": "std::string",
        }[language]

    def default_value(self, language):
        return {
            "cxx": json.dumps(self._value)
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

def main():
    """ Main function """

    events = [Event("We could not lookup the ASN from the probe IP.",
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
               Attribute("""DNS resolver IP address. By setting this option
                            you will force MK to use that DNS resolver for
                            resolving domain names to IP addresses. Otherwise
                            MK will use the system resolver (i.e. it will
                            call `getaddrinfo()`).""",
                         String(), "dns_name_server"),
               Attribute("""Whether to ignore bouncer errors. If this option
                            is true, then MK will not stop after failing to
                            contact the OONI bouncer. Without the information
                            provided by the bouncer, some tests MAY still
                            work, while others (e.g. OONI tests) will most
                            likely fail.""",
                         Bool(True), "ignore_bouncer_error"),
               Attribute("""Max run time for nettests taking input. When you
                            are running a nettest taking input, the test will
                            stop after the number of seconds specified by
                            this option has passed.""",
                         Double(-1.0), "max_runtime")]

    for template_name in sys.argv[1:]:
        template = jinja2.Template(open(template_name, "r").read())
        render = template.render(events=events, options=options)
        print(render)

if __name__ == "__main__":
    main()
