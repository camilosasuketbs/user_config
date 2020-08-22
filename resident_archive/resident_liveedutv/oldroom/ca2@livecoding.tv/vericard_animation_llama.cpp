#include "vericard_animation_llama.h"


namespace vericard
{


   animation_llama::animation_llama(pack * ppack) :
      ::object(ppack->get_app()),
      animation(ppack),
      m_dibDiscoBall(allocer()),
      m_dibLlama(allocer()),
      m_dibLights(allocer()),
      m_dibDisco(allocer())
   {

   }


   animation_llama::~animation_llama()
   {

   }


   bool animation_llama::initialize()
   {

      if (!m_dibDiscoBall.load_from_file(::dir::system() / "config/resident/disco_ball.gif", false))
      {

         return false;

      }

      if (!m_dibLlama.load_from_file(::dir::system() / "config/resident/llama.gif", false))
      {

         return false;

      }

      m_iLlamaFloor = 22;

      return true;

   }

   bool animation_llama::reset()
   {

      m_llama.remove_all();

      m_iLlama = 30;

      m_dwLlama = 1000;

      m_dwLastAddLlama = get_tick_count();

      m_sizeLight = ::size(100, 100);

      light l;

      rect rectClient;

      m_ppack->GetClientRect(rectClient);

      rect rectLights(rectClient);

      rectLights.deflate(m_sizeLight);

      m_lighta.remove_all();

      //for (index i = 0; i < 5; i++)
      //{

      //l.m_pt.x = System.math().RandRange(0, rectLights.width());
      //l.m_pt.y = System.math().RandRange(0, rectLights.height());
      //l.m_dAngle= System.math().frand_range(45.0, 315.0);
      //l.m_dPhase = System.math().frand_range(0.0, 360.0);

      //m_lighta.add(l);

      l.m_pt.x = rectLights.width() / 5;
      l.m_pt.y = rectClient.height() / 3;
      l.m_dAngle = 3.1415 / 6.0;
      l.m_dPhase = System.math().frand_range(0.0, 2.0 * 3.1415);
      l.m_dColor = System.math().frand_range(0.0, 2.0 * 3.1415);
      l.m_dColorSpeed = System.math().frand_range(0.013, 0.04);
      l.m_iBall = 0;

      m_lighta.add(l);

      //}

      l.m_pt.x = rectClient.width() - m_lighta.last().m_pt.x;
      l.m_pt.y = m_lighta.last().m_pt.y;
      l.m_dAngle = 3.1415 * 2.0 - m_lighta.last().m_dAngle;
      l.m_dPhase = System.math().frand_range(0.0, 2.0 * 3.1415);
      l.m_dColor = System.math().frand_range(0.0, 2.0 * 3.1415);
      l.m_dColorSpeed = System.math().frand_range(0.013, 0.04);
      l.m_iBall = 1;

      m_lighta.add(l);


      l.m_pt.x = rectLights.width() / 3;
      l.m_pt.y = rectClient.height() * 3 / 4;
      l.m_dAngle = 3.1415 / 3.0;
      l.m_dPhase = System.math().frand_range(0.0, 2.0 * 3.1415);
      l.m_dColor = System.math().frand_range(0.0, 2.0 * 3.1415);
      l.m_dColorSpeed = System.math().frand_range(0.013, 0.04);
      l.m_iBall = 0;

      m_lighta.add(l);

      //}

      l.m_pt.x = rectClient.width() - m_lighta.last().m_pt.x;
      l.m_pt.y = m_lighta.last().m_pt.y;
      l.m_dAngle = 3.1415 * 2.0 - m_lighta.last().m_dAngle;
      l.m_dPhase = System.math().frand_range(0.0, 2.0 * 3.1415);
      l.m_dColor = System.math().frand_range(0.0, 2.0 * 3.1415);
      l.m_dColorSpeed = System.math().frand_range(0.013, 0.04);
      l.m_iBall = 1;

      m_lighta.add(l);

      return true;

   }

   void animation_llama::defer_add_llama()
   {

      if (m_ppack->m_strAnimationStyleNew != m_ppack->m_strAnimationStyle)
      {

         m_bChange = true;

      }

      for (index i = 0; i < m_llama.get_count(); )
      {

         rect rectClient;

         m_ppack->GetClientRect(rectClient);

         if (m_llama[i].m_iOffset >(rectClient.right + 300))
         {

            m_llama.remove_at(i);

         }
         else
         {

            i++;

         }

      }

      if (m_bChange)
      {

         if (m_llama.get_count() <= 0)
         {

            m_ppack->m_strAnimationStyle = m_ppack->m_strAnimationStyleNew;

            reset();

            m_bChange = false;

         }

         return;

      }

      if (m_iLlama <= 0)
      {

         return;

      }

      if (get_tick_count() - m_dwLastAddLlama < m_dwLlama)
      {

         return;

      }

      m_dwLastAddLlama = get_tick_count();

      if (m_ppack->m_strAnimationStyle == "sync")
      {

         m_dwLlama = 3000;

      }
      else
      {

         m_dwLlama = System.math().RandRange(3000, 5000);

      }

      m_iLlama--;

      llama l;

      l.m_iLastTop = -1;
      l.m_dVel = 0.0;
      l.m_dSize = System.math().frand_range(0.8, 1.3);
      if (m_ppack->m_strAnimationStyle == "sync")
      {
         l.m_dSpeed = 1.0 / l.m_dSize;
      }
      else
      {
         l.m_dSpeed = System.math().frand_range(0.8, 1.3);
      }
      l.m_iOffset = -m_dibLlama->m_size.cx * 2.0;
      l.m_dColor = System.math().frand_range(0.0, 2 * 3.1415);
      l.m_dColorSpeed = System.math().frand_range(0.013, 0.04);
      l.m_rect = ::rect(null_point(), m_dibLlama->m_size * l.m_dSize);
      l.m_dib.alloc(allocer());
      l.m_dib->create(l.m_rect.get_size());
      m_llama.add(l);

   }


   void animation_llama::_001OnDrawBefore(::draw2d::graphics * pgraphics)
   {

      defer_add_llama();

      rect rectClient;

      m_ppack->GetClientRect(rectClient);

      //if (m_iLastTop < 0)
      //{

      //   m_rectDisco = ::rect(::null_point(), m_dibDiscoBall->m_size);

      //}

      {



         //m_dibDiscoBall.m_dSpeed = 4.1;

         //m_dibDiscoBall.defer_update();

         //pgraphics->StretchBlt(m_rectDisco.left, m_rectDisco.top,
         // m_rectDisco.width(), m_rectDisco.height(),
         //m_dibDiscoBall->get_graphics(), 0, 0, m_dibDiscoBall->m_size.cx, m_dibDiscoBall->m_size.cy);
         ::rect rShell;


#ifdef WINDOWSEX
         HWND hwnd = ::FindWindow("Shell_TrayWnd", NULL);

         ::GetWindowRect(hwnd, rShell);
#else

	rShell = rectClient;

	rShell.top = rShell.bottom;

#endif

         for (index i = 0; i < m_llama.get_count(); i++)
         {

            llama & l = m_llama[i];

            rect & rDisco = l.m_rect;

            double dNewVel = 0;

            rect rUtil(rectClient);

            rUtil.deflate(2, 2);

            if (l.m_iLastTop >= 0)
            {

               dNewVel = rShell.top - l.m_iLastTop;

            }

            double dAccel = 1.2; // please consider the object interaction with the air

            if (rShell.top < rDisco.bottom)
            {

               rDisco.move_to(0, rShell.top - rDisco.height());

               l.m_dVel = rDisco.bottom - l.m_iLastTop;

               l.m_dVel /= 3.0;

            }
            else if (l.m_dVel > 1.0)
            {

               l.m_dVel = l.m_dVel / dAccel;

               rDisco.offset(0, -l.m_dVel);

            }
            else
            {

               if (l.m_dVel >= 0.0)
               {

                  l.m_dVel = -1.0;

               }
               else
               {
                  l.m_dVel = l.m_dVel * dAccel;
               }

               rDisco.offset(0, -l.m_dVel);

               if (rShell.top < rDisco.bottom)
               {

                  l.m_dVel = -l.m_dVel * 0.6;

                  rDisco.move_to(0, rShell.top - rDisco.height());

               }

            }

            m_dibLlama.m_dSpeed = l.m_dSpeed;

            m_dibLlama.defer_update();

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            l.m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

            l.m_dib->get_graphics()->StretchBlt(0, 0,
               rDisco.width(), rDisco.height(),
               m_dibLlama->get_graphics(), 0, 0, m_dibLlama->m_size.cx, m_dibLlama->m_size.cy);

            l.m_dib->hue_offset(l.m_dColor);

            l.m_dColor += l.m_dColorSpeed;

            pgraphics->draw_dim(l.m_iOffset, rDisco.top + m_iLlamaFloor * l.m_dSize,
               rDisco.width(), rDisco.height(),
               l.m_dib->get_graphics());

            l.m_iOffset += m_dibLlama->m_size.cx * l.m_dSize*l.m_dSpeed / 40.0;

            l.m_iLastTop = rDisco.top;

         }



      }


      //      rect rectClient;

      //    m_ppack->GetClientRect(rectClient);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      rect rLights(rectClient);

      rLights.offset(-rLights.top_left());

      m_dibLights->create(rLights.get_size());

      m_dibLights->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      m_dibLights->get_graphics()->fill_solid_rect(rLights, ARGB(127, 0, 0, 0));

      ::draw2d::brush_sp br(allocer());

      int w = rectClient.width();
      int h = rectClient.width();
      int iM = rectClient.width() / 2;


      m_dBallDistance = 101.0;

      m_dLightAperture = 5.0;

      POINTD pta[3];

      for (index i = 0; i < m_lighta.get_count(); i++)
      {

         m_dibLights->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
         light & l = m_lighta[i];

         double o = m_dPhase + l.m_dPhase;

         if (l.m_iBall == 1)
         {

            o = -o;

         }

         double y = l.m_pt.y;
         double x = l.m_pt.x + (m_dBallDistance + y) * tan(o);
         double a = x;
         double b = y;
         //double a = x * cos(l.m_dAngle) - y * sin(l.m_dAngle);
         //double b = x * sin(l.m_dAngle) + y * cos(l.m_dAngle);
         int m = x;
         int cx = (m_dBallDistance + b) * (tan(o + m_dLightAperture / 2.0) - tan(o - m_dLightAperture / 2.0));
         int cy = 380.0;
         //double p = x * cos(l.m_dAngle) - y * sin(l.m_dAngle);
         //double q = x * sin(l.m_dAngle) + y * cos(l.m_dAngle);
         double p = a;
         double q = b;

         if (cx < 0)
         {

            p += cx;

            cx = -cx;

         }

         rect rLight(p, q, p+cx, q+cy);

         color clr;

         clr.set_hls(0.0, 0.75, 1.0);

         clr.hue_offset(l.m_dColor);

         color clr2;

         clr2.set_hls(0.0, 0.75, 0.7);

         clr2.hue_offset(l.m_dColor);

         l.m_dColor += l.m_dColorSpeed;

         ::draw2d::path_sp path(allocer());

         path->begin_figure(true, ::draw2d::fill_mode_winding);

         if (l.m_iBall == 0)
         {

            pta[0].x = rectClient.width() / 4;

         }
         else
         {

            pta[0].x = 3 * rectClient.width() / 4;

         }

         pta[0].y = -m_dBallDistance * 4.0;

         pta[1].x = p;
         pta[1].y = q + cy / 2;

         pta[2].x = p + cx;
         pta[2].y = q + cy / 2;

         path->add_lines(pta, 3);

         path->end_figure(true);

         clr2.m_uchA = 33;

         br->create_solid(clr2.get_rgba());

         m_dibLights->get_graphics()->fill_path(path, br);

         clr.m_uchA = 44;

         br->create_solid(clr.get_rgba());

         m_dibLights->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         m_dibLights->get_graphics()->SelectObject(br);

         m_dibLights->get_graphics()->FillEllipse(rLight);

      }


      {

         double dTime = get_tick_count();

         dTime /= 1000.0; // in seconds

         double dFrequency = 0.1; // in Hz

         double dOmega = 2.0 * 3.1415 * dFrequency; // radians / per second

         m_dPhase = dOmega * dTime;

         m_dPhase = fmod(m_dPhase, 3.1415 * 2.0);

      }





      pgraphics->draw(rectClient, m_dibLights->get_graphics());




      //if (m_iLastTop < 0)
      //{

      //   m_rectDisco = ::rect(::null_point(), m_dibDiscoBall->m_size);

      //}


   }

   void animation_llama::_001OnDrawAfter(::draw2d::graphics * pgraphics)
   {


      rect rectClient;

      m_ppack->GetClientRect(rectClient);


      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      {

         m_dibDiscoBall.m_dSpeed = 2.0;

         m_dibDiscoBall.defer_update();

         rect rectDisco(::null_point(), m_dibDiscoBall->m_size * 2);

         rectDisco.Align(align_top_center, rectClient);

         m_dibDisco->create(rectDisco.get_size());

         m_dibDisco->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         //m_dibDisco->get_graphics()->fill_solid_rect(0, 0, , m_dibDiscoBall->m_size.cx, m_dibDiscoBall->m_size.cy, ARGB(255, 0, 255, 0));

         if (m_bShutdownRequest || m_bChange)
         {

            m_dibDisco->get_graphics()->alpha_blend(0, 0,
               rectDisco.width(), rectDisco.height(),
               m_dibDiscoBall->get_graphics(), 0, 0, m_dibDiscoBall->m_size.cx, m_dibDiscoBall->m_size.cy, 0.5);

         }
         else
         {
            m_dibDisco->get_graphics()->StretchBlt(0, 0,
               rectDisco.width(), rectDisco.height(),
               m_dibDiscoBall->get_graphics(), 0, 0, m_dibDiscoBall->m_size.cx, m_dibDiscoBall->m_size.cy);

         }
         
         m_dibDisco->hue_offset(m_dDiscoColor);

         m_dDiscoColor += 0.02;

         pgraphics->draw(rectDisco, m_dibDisco->get_graphics());

      }

   }


} // namespace vericard



