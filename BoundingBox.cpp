#include "BoundingBox.h"


BoundingBox::BoundingBox(float width, float height, float depth)
{
   use = false;
   set(width, height, depth);
}


BoundingBox::~BoundingBox(void)
{
}

void BoundingBox::set(float width, float height, float depth)
{
   if(width >= 0) this->width = width;
   if(height >= 0) this->height = height;
   if(depth >= 0) this->depth = depth;
}


float BoundingBox::getWidth() const
{
   return width;
}

float BoundingBox::getHeight() const
{
   return height;
}

float BoundingBox::getDepth() const
{
   return depth;
}

glm::vec3 BoundingBox::getCenter() const
{
   return glm::vec3(orientation[3]);
}

glm::vec3 BoundingBox::getFrontNormal() const
{
   return glm::vec3(orientation[2]);
}

glm::vec3 BoundingBox::getUpNormal() const
{
   return glm::vec3(orientation[1]);
}

glm::vec3 BoundingBox::getRightNormal() const
{
   return glm::vec3(orientation[0]);
}


float BoundingBox::getProjection(const glm::vec3& vector, const glm::vec3& pAxis) const
{
   glm::vec3 pUnit = glm::normalize(pAxis);
   return glm::dot(vector, pAxis);
}

bool BoundingBox::overlapsWith(const BoundingBox& other)
{
   if(!use || !other.use) return false;

   float wa = getWidth()/2;
   float ha = getHeight()/2;
   float da = getDepth()/2;

   glm::vec3 Ca = getCenter();
   glm::vec3 Az = getFrontNormal();
   glm::vec3 Ay = getUpNormal();
   glm::vec3 Ax = getRightNormal();

   glm::vec3 Cb = other.getCenter();
   glm::vec3 Bz = other.getFrontNormal();
   glm::vec3 By = other.getUpNormal();
   glm::vec3 Bx = other.getRightNormal();
   float wb = other.getWidth()/2;
   float hb = other.getHeight()/2;
   float db = other.getDepth()/2;

   glm::vec3 T = Cb - Ca;

   float lhs = 0, rhs = 0;

   float Rxx = glm::dot(Ax, Bx);
   float Rxy = glm::dot(Ax, By);
   float Rxz = glm::dot(Ax, Bz);

   // Case 1: L = Ax
   lhs = glm::dot(T, Ax);
   rhs = wa + fabs(wb * Rxx) + fabs(hb * Rxy) + fabs(db * Rxz);
   if(lhs > rhs) return false;

   float Ryx = glm::dot(Ay, Bx);
   float Ryy = glm::dot(Ay, By);
   float Ryz = glm::dot(Ay, Bz);

   // Case 2: L = Ay
   lhs = glm::dot(T, Ay);
   rhs = ha + fabs(wb * Ryx) + fabs(hb * Ryy) + fabs(db * Ryz);
   if(lhs > rhs) return false;

   float Rzx = glm::dot(Az, Bx);
   float Rzy = glm::dot(Az, By);
   float Rzz = glm::dot(Az, Bz);

   // Case 3: L = Az
   lhs = glm::dot(T, Az);
   rhs = da + fabs(wb * Rzx) + fabs(hb * Rzy) + fabs(db * Rzz);
   if(lhs > rhs) return false;

   // Case 4: L = Bx
   lhs = glm::dot(T, Bx);
   rhs = fabs(wa * Rxx) + fabs(ha * Ryx) + fabs(da * Rzx) + wb;
   if(lhs > rhs) return false;

   // Case 5: L = By
   lhs = glm::dot(T, By);
   rhs = fabs(wa * Rxy) + fabs(ha * Ryy) + fabs(da * Rzy) + hb;
   if(lhs > rhs) return false;

   // Case 6: L = Bz
   lhs = glm::dot(T, Bz);
   rhs = fabs(wa * Rxz) + fabs(ha * Ryz) + fabs(da * Rzz) + db;
   if(lhs > rhs) return false;

   // Case 7: L = Ax x Bx
   lhs = glm::dot(T, glm::cross(Ax, Bx));
   rhs = fabs(ha * Rzx) + fabs(da * Ryx) + fabs(hb * Rxz) + fabs(db * Rxy);
   if(lhs > rhs) return false;

   // Case 8: L = Ax x By
   lhs = glm::dot(T, glm::cross(Ax, By));
   rhs = fabs(ha * Rzy) + fabs(da * Ryy) + fabs(wb * Rxz) + fabs(db * Rxx);
   if(lhs > rhs) return false;

   // Case 9: L = Ax x Bz
   lhs = glm::dot(T, glm::cross(Ax, Bz));
   rhs = fabs(ha * Rzz) + fabs(da * Ryz) + fabs(wb * Rxy) + fabs(hb * Rxx);
   if(lhs > rhs) return false;

   // Case 10: L = Ay x Bx
   lhs = glm::dot(T, glm::cross(Ay, Bx));
   rhs = fabs(wa * Rzx) + fabs(da * Rxx) + fabs(hb * Ryz) + fabs(db * Ryy);
   if(lhs > rhs) return false;

   // Case 11: L = Ay x By
   lhs = glm::dot(T, glm::cross(Ay, By));
   rhs = fabs(wa * Rzy) + fabs(da * Rxy) + fabs(wb * Ryz) + fabs(db * Ryx);
   if(lhs > rhs) return false;

   // Case 12: L = Ay x Bz
   lhs = glm::dot(T, glm::cross(Ay, Bz));
   rhs = fabs(wa * Rzz) + fabs(da * Rxz) + fabs(wb * Ryy) + fabs(hb * Ryx);
   if(lhs > rhs) return false;

   // Case 13: L = Az x Bx
   lhs = glm::dot(T, glm::cross(Az, Bx));
   rhs = fabs(wa * Ryx) + fabs(ha * Rxx) + fabs(hb * Rzz) + fabs(db * Rzy);
   if(lhs > rhs) return false;

   // Case 14: L = Az x By
   lhs = glm::dot(T, glm::cross(Az, By));
   rhs = fabs(wa * Ryy) + fabs(ha * Rxy) + fabs(wb * Rzz) + fabs(db * Rzx);
   if(lhs > rhs) return false;

   // Case 15: L = Az x Bz
   lhs = glm::dot(T, glm::cross(Az, Bz));
   rhs = fabs(wa * Ryz) + fabs(ha * Rxz) + fabs(wb * Rzy) + fabs(hb * Rzx);
   if(lhs > rhs) return false;

   return true;
}
