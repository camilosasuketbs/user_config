#include "animation_disco.h"


namespace resident
{


   animation_disco::animation_disco(main_stage * pmainstage) :
      ::object(pmainstage->get_app()),
      animation(pmainstage)
   {
      m_iPerson = 0;
      m_imageDiscoBall.alloc(this);
      m_imageLights.alloc(this);
      m_imageDisco.alloc(this);
      m_imagePerson.alloc(this);
      if (!m_imageDiscoBall.load_image(Application.resident_get_app_path("resident") / "disco_ball.gif", false))
      {

         output_debug_string("couldn't load disco_ball image");

      }

      ::file::path path = Application.resident_get_app_path("resident") / "person.gif";

      if(!m_imagePerson.load_image(path, false))
      {

         output_debug_string("couldn't load \"unknown\" person image");


      }


      m_iLlamaFloor = 22;

   }


   animation_disco::~animation_disco()
   {

   }


   bool animation_disco::on_started()
   {

      m_iPerson = 0;
      m_llama.remove_all();

      m_usera.remove_all();

      for(int i = 0; i < Application.mainstage().m_commptra.get_count(); i++)
      {

         auto comm = Application.mainstage().m_commptra[i];

         stringa straUsers;

         comm->get_present_users(straUsers);

         for(int j = 0 ; j < straUsers.get_count(); j++)
         {

            __pointer(::resident::user) puser = comm->get_user(straUsers[j], true);

            m_usera.add(puser);

         }

      }

      m_iLlama = 20;

      m_tickLlama = 1000;

      m_tickLastAddLlama.Now();

      m_sizeLight = ::size(100, 100);

      light l;

      auto rectClient = m_pmainstage->get_client_rect();

      rect rectLights(rectClient);

      rectLights.deflate(m_sizeLight);

      m_lighta.remove_all();

      //for (index i = 0; i < 5; i++)
      //{

      //l.m_pt.x = System.math().RandRange(0, rectLights.width());
      //l.m_pt.y = System.math().RandRange(0, rectLights.height());
      //l.m_dAngle= __random(45.0, 315.0);
      //l.m_dPhase = __random(0.0, 360.0);

      //m_lighta.add(l);

      l.m_pt.x = rectLights.width() / 5;
      l.m_pt.y = rectClient.height() / 3;
      l.m_dAngle = 3.1415 / 6.0;
      l.m_dPhase = __random(0.0, 2.0 * 3.1415);
      l.m_dColor = __random(0.0, 2.0 * 3.1415);
      l.m_dColorSpeed = __random(0.013, 0.04);
      l.m_iBall = 0;

      m_lighta.add(l);

      //}

      l.m_pt.x = rectClient.width() - m_lighta.last().m_pt.x;
      l.m_pt.y = m_lighta.last().m_pt.y;
      l.m_dAngle = 3.1415 * 2.0 - m_lighta.last().m_dAngle;
      l.m_dPhase = __random(0.0, 2.0 * 3.1415);
      l.m_dColor = __random(0.0, 2.0 * 3.1415);
      l.m_dColorSpeed = __random(0.013, 0.04);
      l.m_iBall = 1;

      m_lighta.add(l);


      l.m_pt.x = rectLights.width() / 3;
      l.m_pt.y = rectClient.height() * 3 / 4;
      l.m_dAngle = 3.1415 / 3.0;
      l.m_dPhase = __random(0.0, 2.0 * 3.1415);
      l.m_dColor = __random(0.0, 2.0 * 3.1415);
      l.m_dColorSpeed = __random(0.013, 0.04);
      l.m_iBall = 0;

      m_lighta.add(l);

      //}

      l.m_pt.x = rectClient.width() - m_lighta.last().m_pt.x;
      l.m_pt.y = m_lighta.last().m_pt.y;
      l.m_dAngle = 3.1415 * 2.0 - m_lighta.last().m_dAngle;
      l.m_dPhase = __random(0.0, 2.0 * 3.1415);
      l.m_dColor = __random(0.0, 2.0 * 3.1415);
      l.m_dColorSpeed = __random(0.013, 0.04);
      l.m_iBall = 1;

      m_lighta.add(l);

      return true;

   }

   void animation_disco::defer_add_llama()
   {


      for (index i = 0; i < m_llama.get_count(); )
      {

         rect rectClient = m_pmainstage->get_client_rect();

         if (m_llama[i]->m_iOffset >(rectClient.right + 300))
         {

            m_llama.remove_at(i);

         }
         else
         {

            i++;

         }

      }


      if (m_llama.get_count() <= 0)
      {

         on_finished_animation();
   
      }

      if (m_iLlama <= 0)
      {

         return;

      }

      if (m_tickLastAddLlama.elapsed() < m_tickLlama)
      {

         return;

      }

      m_tickLastAddLlama.Now();

      if (m_pmainstage->m_strAnimationStyle == "sync")
      {

         m_tickLlama = 3000;

      }
      else
      {

         m_tickLlama = __random(3000, 5000);

      }

      m_iLlama--;

      __pointer(llama)  l = __sp(new llama);

      l->m_iPerson = m_iPerson;
      m_iPerson++;
      l->m_iLastTop = -1;
      l->m_dVel = 0.0;
      l->m_dSize = __random(0.8, 1.3);
      if (m_pmainstage->m_strAnimationStyle == "sync")
      {
         l->m_dSpeed = 1.0 / l->m_dSize;
      }
      else
      {
         l->m_dSpeed = __random(0.8, 1.3);
      }
      l->m_iOffset = -m_imagePerson.width() * 2.0;
      l->m_dColor = __random(0.0, 2 * 3.1415);
      l->m_dColorSpeed = __random(0.013, 0.04);
      l->m_rect = ::rect(::point(), m_imagePerson.size() * l->m_dSize);
      l->m_image.alloc(this);
      l->m_image.create(l->m_rect.size());
      l->m_imageHead.alloc(this);
      l->m_imageHead.create(l->m_rect.size());
      m_llama.add(l);

   }


   void animation_disco::_001OnDrawBefore(::draw2d::graphics * pgraphics)
   {

      defer_add_llama();

      auto rectClient = m_pmainstage->get_client_rect();

      //if (m_iLastTop < 0)
      //{

      //   m_rectDisco = ::rect(::null_point(), m_imageDiscoBall.size());

      //}

      {



         //m_imageDiscoBall.m_dSpeed = 4.1;

         //m_imageDiscoBall.defer_update();

         //pgraphics->StretchBlt(m_rectDisco.left, m_rectDisco.top,
         // m_rectDisco.width(), m_rectDisco.height(),
         //m_imageDiscoBall.g(), 0, 0, m_imageDiscoBall.width(), m_imageDiscoBall.height());
         ::rect rShell;


#ifdef WINDOWSEX
         HWND hwnd = ::FindWindowW(L"Shell_TrayWnd", NULL);

         ::GetWindowRect(hwnd, rShell);
#else

         rShell = rectClient;

         rShell.top = rShell.bottom;

#endif

         for (index i = 0; i < m_llama.get_count(); i++)
         {

            llama & l = *m_llama[i];

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

            rect rHead;

            rect rAlign;

            rAlign.left = rDisco.left + rDisco.width() / 4;
            rAlign.right = rDisco.right - rDisco.width() / 4;
            rAlign.top = rDisco.top + rDisco.width() / 6;
            rAlign.bottom = rAlign.top + rAlign.width();

            __pointer(::resident::user) puser;

            if (m_usera.has_elements())
            {

               puser = m_usera[l.m_iPerson % m_usera.get_count()];

            }

            synch_lock sl(puser ? puser->m_pmutex : nullptr);

            ::image image;

            if (puser.is_set())
            {

               image = puser->m_imageCircle;

            }

            if(image)
            {

               rHead.left = 0;
               rHead.top = 0;
               rHead.right = image.width() * l.m_dSize * 1.2;
               rHead.bottom = image.height() * l.m_dSize * 1.2;

               rHead.Align(align_center, rAlign);

               //image->m_dSpeed = l.m_dSpeed;

               //image->defer_update();

            }

            m_imagePerson.m_pimpl->m_dSpeed = l.m_dSpeed;

            m_imagePerson.defer_update();

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            l.m_image.g()->set_alpha_mode(::draw2d::alpha_mode_set);

            l.m_image.g()->StretchBlt(0, 0,
                                      rDisco.width(), rDisco.height(),
                                      m_imagePerson.g(), 0, 0, m_imagePerson.width(), m_imagePerson.height());

            if (image)
            {

               int iFirst = 0;

               for (index i = 0; i < m_imagePerson.height(); i++)
               {

                  if (argb_get_a_value(m_imagePerson.pixel(m_imagePerson.width() / 2, i)) > 0x33)
                  {

                     iFirst = i;

                     break;

                  }

               }

               l.m_image.g()->set_alpha_mode(::draw2d::alpha_mode_blend);

               l.m_image.g()->StretchBlt(rHead.left -rDisco.left,(LONG) MAX(0, iFirst * l.m_dSize - 5),
                                         rHead.width(), rHead.height(),
                                         image.g(), 0, 0, image.width(), image.height());

            }

            l.m_image.hue_offset(l.m_dColor);

            l.m_dColor += l.m_dColorSpeed;

            pgraphics->draw_dim(l.m_iOffset, rDisco.top + m_iLlamaFloor * l.m_dSize,
                                rDisco.width(), rDisco.height(),
                                l.m_image.g());

            l.m_iOffset += m_imagePerson.width() * l.m_dSize*l.m_dSpeed / 30.0;

            l.m_iLastTop = rDisco.top;

         }



      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      rect rLights(rectClient);

      rLights.offset(-rLights.top_left());

      m_imageLights.create(rLights.size());

      m_imageLights.g()->set_alpha_mode(::draw2d::alpha_mode_set);

      m_imageLights.g()->fill_solid_rect(rLights, ARGB(127, 0, 0, 0));

      ::draw2d::brush_sp br(create_new, this);

      int w = rectClient.width();
      int h = rectClient.width();
      int iM = rectClient.width() / 2;


      m_dBallDistance = 101.0;

      m_dLightAperture = 5.0;

      POINTD pta[3];

      for (index i = 0; i < m_lighta.get_count(); i++)
      {

         m_imageLights.g()->set_alpha_mode(::draw2d::alpha_mode_blend);
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

         ::draw2d::path_sp path(create_new, this);

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

         clr2.m_iA = 33;

         br->create_solid(clr2.get_rgba());

         m_imageLights.g()->fill_path(path, br);

         clr.m_iA = 44;

         br->create_solid(clr.get_rgba());

         m_imageLights.g()->set_alpha_mode(::draw2d::alpha_mode_set);

         m_imageLights.g()->SelectObject(br);

         m_imageLights.g()->fill_ellipse(rLight);

      }


      {

         auto dTime = __double(::tick::now());

         dTime /= 1000.0; // in seconds

         double dFrequency = 0.1; // in Hz

         double dOmega = 2.0 * 3.1415 * dFrequency; // radians / per second

         m_dPhase = dOmega * dTime;

         m_dPhase = fmod(m_dPhase, 3.1415 * 2.0);

      }





      pgraphics->draw(rectClient, m_imageLights.g());




      //if (m_iLastTop < 0)
      //{

      //   m_rectDisco = ::rect(::null_point(), m_imageDiscoBall.size());

      //}


   }

   void animation_disco::_001OnDrawAfter(::draw2d::graphics * pgraphics)
   {


      auto rectClient = m_pmainstage->get_client_rect();


      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      {

         m_imageDiscoBall.m_pimpl->m_dSpeed = 2.0;

         m_imageDiscoBall.defer_update();

         rect rectDisco(::point(), m_imageDiscoBall.size() * 2);

         rectDisco.Align(align_top_center, rectClient);

         m_imageDisco.create(rectDisco.size());

         m_imageDisco.g()->set_alpha_mode(::draw2d::alpha_mode_set);

         //m_imageDisco.g()->fill_solid_rect(0, 0, , m_imageDiscoBall.width(), m_imageDiscoBall.height(), ARGB(255, 0, 255, 0));

         if (m_bStop || m_bChanged)
         {

            m_imageDisco.g()->alpha_blend(0, 0,
                                          rectDisco.width(), rectDisco.height(),
                                          m_imageDiscoBall.g(), 0, 0, m_imageDiscoBall.width(), m_imageDiscoBall.height(), 0.5);

         }
         else
         {
            m_imageDisco.g()->StretchBlt(0, 0,
                                         rectDisco.width(), rectDisco.height(),
                                         m_imageDiscoBall.g(), 0, 0, m_imageDiscoBall.width(), m_imageDiscoBall.height());

         }
         m_imageDisco.hue_offset(m_dDiscoColor);

         m_dDiscoColor += 0.02;
         pgraphics->draw(rectDisco, m_imageDisco.g());

      }

   }


} // namespace resident



