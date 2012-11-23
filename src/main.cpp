

#include "socket_io_client.hpp"
#include <stdio.h>

using namespace socketio;

int main(int /*argc*/, char* /*argv*/ []) {
   // websocket++ expects urls to begin with "ws://" not "http://"
   std::string uri = "ws://ruth:8888/client";

   try {
      // Create and link handler to websocket++ callbacks.
      socketio_client_handler_ptr handler(new socketio_client_handler());
      client::connection_ptr con;
      client endpoint(handler);

      // Set log level. Leave these unset for no logging, or only set a few for selective logging.
      endpoint.elog().set_level(websocketpp::log::elevel::RERROR);
      endpoint.elog().set_level(websocketpp::log::elevel::FATAL);
      endpoint.elog().set_level(websocketpp::log::elevel::WARN);
      endpoint.alog().set_level(websocketpp::log::alevel::DEVEL);

      handler->bind_event("misc", &socketio_events::example);

      std::string socket_io_uri = handler->perform_handshake(uri);
      con = endpoint.get_connection(socket_io_uri);

      // The previous two lines can be combined:
      // con = endpoint.get_connection(handler->perform_handshake(uri));

      endpoint.connect(con);

      boost::thread t(boost::bind(&client::run, &endpoint, false));

      // Wait for a sec before sending stuff
      int i=0;
      while (!handler->connected()) {
        while(i<1000) i++;
        i=0;
      }

const char json[] ="{\"pseudo\":\"I am a c++ guy\",\"p_class\":\"dwarf\"}";

        rapidjson::Document d;
        //d.Parse<0>(json);

       Value n;
       n.SetString("I am a c++ guy");//name.c_str(), name.length(), args.GetAllocator());
       d.AddMember("pseudo",n);

       Value m;
       m.SetString("dwarf");//name.c_str(), name.length(), args.GetAllocator());
       d.AddMember("p_class",m);

      handler->nspace("/client");
      handler->emit("my pseudo",d,"/client");//"{\"pseudo\":\"alligator\"}");

     

        t.join();
            //  endpoint.stop(false);
   }
   catch (std::exception& e) {
      std::cerr << "Exception: " << e.what() << std::endl;
      std::getchar();
   }
}
