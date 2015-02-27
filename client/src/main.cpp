#include "logger.h"
#include "main.h"

bool MyApp::OnInit()
{
  if (!wxApp::OnInit()) return false;

  init_log(argc, argv);
  LOG(INFO) << "Initializing";

  frame = new MainWindow("Hello World", wxPoint(50, 50), wxSize(300, 400));
  manager = new ChunkManager();

  return true;
}

int MyApp::OnExit()
{
  delete m_glContext;
  delete manager;
  return wxApp::OnExit();
}

GraphicsContext& MyApp::GetContext(wxGLCanvas* canvas)
{
  GraphicsContext* glContext;
  if (!m_glContext)
  {
    // Create the OpenGL context for the first mono window which needs it:
    // subsequently created windows will all share the same context.
    m_glContext = new GraphicsContext(canvas);
  }
  glContext = m_glContext;

  glContext->SetCurrent(*canvas);

  return *glContext;
}

wxIMPLEMENT_APP(MyApp);
