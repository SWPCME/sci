[+ AutoGen5 template hxx +]
[+ amg_tpl_head +]
[+ Include "cxx_licence.cxx" +]

#ifndef [+ file_def +]
#define [+ file_def +]

namespace [+ namespace_name +]
{
    class [+ lib +] [+ class_name +]
    {
      public:
        [+ class_name +]();
        ~[+ class_name +]();

        UErrCodeT Init();

      protected:
      private:
    };
}
 
#endif  // [+ file_def +]
