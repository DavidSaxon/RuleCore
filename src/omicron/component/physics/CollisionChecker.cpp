#include "CollisionChecker.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

CollisionChecker::CollisionChecker( const std::string& id ) :
    Physics( id )
{
}

CollisionChecker::CollisionChecker(
        const std::string& id,
        const std::vector<BoundingShape*>& boundings )
    :
    Physics( id ),
    m_boundings( boundings )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

const std::vector<BoundingShape*> CollisionChecker::getBoundings() const
{
    return m_boundings;
}

void CollisionChecker::addBounding( BoundingShape* bounding )
{
    m_boundings.push_back( bounding );
}

bool CollisionChecker::forwardCheck(
        const glm::vec3& move,
        const std::string& group )
{
    bool collision = false;
    // check each bounding
    for ( std::vector<BoundingShape*>::iterator it = m_boundings.begin();
          it != m_boundings.end(); ++it )
    {
        BoundingShape* bounding = *it;

        // change the position of the transform of the bounding
        glm::vec3 orginalPos = bounding->getTransform()->translation;
        glm::vec3 newPos = orginalPos + move;
        bounding->getTransform()->translation = newPos;

        if ( !CollisionDetect::checkAgainstGroup( bounding, group ).empty() )
        {
            collision = true;
            // reset position
            bounding->getTransform()->translation = orginalPos;
            break;
        }

        // reset position
        bounding->getTransform()->translation = orginalPos;
    }

    return collision;
}

glm::vec3 CollisionChecker::forwardBestCheck(
            const glm::vec3& move,
            const std::string& group )
{
    BoundingShape* colliderBounding = NULL;
    std::vector<BoundingShape*> collisionBoundings;
    // check each bounding
    for ( std::vector<BoundingShape*>::iterator it = m_boundings.begin();
          it != m_boundings.end(); ++it )
    {
        BoundingShape* bounding = *it;

        // change the position of the transform of the bounding
        glm::vec3 orginalPos = bounding->getTransform()->translation;
        glm::vec3 newPos = orginalPos + move;
        bounding->getTransform()->translation = newPos;

        const std::vector<BoundingShape*> b =
                CollisionDetect::checkAgainstGroup( bounding, group );
        if ( !b.empty() )
        {
            colliderBounding = bounding;
            collisionBoundings = b;
            // reset position
            bounding->getTransform()->translation = orginalPos;
            break;
        }

        // reset position
        bounding->getTransform()->translation = orginalPos;
    }

    if ( colliderBounding != NULL && !collisionBoundings.empty() )
    {
        // make a copy of the movement vector
        glm::vec3 new_move( move );

        for ( std::vector<BoundingShape*>::iterator it =
              collisionBoundings.begin(); it != collisionBoundings.end(); ++it )
        {
            // TODO: should support other shapes
            // cast to rectangle
            BoundingRect* rect1 =
                    static_cast<BoundingRect*>( colliderBounding );
            BoundingRect* rect2 = static_cast<BoundingRect*>( *it );

            // calculate the best position
            glm::vec3 temp_move( 0.0f, 0.0f, 0.0f );

            // TODO: bounding ALL?
            // apply shift movement
            if ( rect2->getDirection() == bounding::UP )
            {
                float minDis = ( rect1->getSize().y / 2.0f ) +
                               ( rect2->getSize().y / 2.0f );
                minDis = -minDis;
                float dis = rect1->getTransform()->translation.z;
                dis = rect2->getTransform()->translation.z - dis;
                dis -= new_move.z;
                temp_move.z = minDis - dis;

                if ( new_move.z <= 0.0f && new_move.z - temp_move.z <= 0.01f )
                {
                    new_move.z = new_move.z - temp_move.z;
                }
            }
            else if ( rect2->getDirection() == bounding::RIGHT )
            {
                float minDis = ( rect1->getSize().x / 2.0f ) +
                               ( rect2->getSize().x / 2.0f );
                float dis = rect1->getTransform()->translation.x;
                dis = rect2->getTransform()->translation.x - dis;
                dis -= new_move.x;
                temp_move.x = minDis - dis;

                if ( new_move.x >= 0.0f && new_move.x - temp_move.x >= -0.01f )
                {
                    new_move.x = new_move.x - temp_move.x;
                }
            }
            else if ( rect2->getDirection() == bounding::DOWN )
            {
                float minDis = ( rect1->getSize().y / 2.0f ) +
                               ( rect2->getSize().y / 2.0f );
                float dis = rect1->getTransform()->translation.z;
                dis = rect2->getTransform()->translation.z - dis;
                dis -= new_move.z;
                temp_move.z = minDis - dis;

                if ( new_move.z >= 0.0f && new_move.z - temp_move.z >= -0.01f )
                {
                    new_move.z = new_move.z - temp_move.z;
                }
            }
            else if ( rect2->getDirection() == bounding::LEFT )
            {
                float minDis = ( rect1->getSize().x / 2.0f ) +
                               ( rect2->getSize().x / 2.0f );
                minDis = -minDis;
                float dis = rect1->getTransform()->translation.x;
                dis = rect2->getTransform()->translation.x - dis;
                dis -= new_move.x;
                temp_move.x = minDis - dis;

                if ( new_move.x <= 0.0f && new_move.x - temp_move.x <= 0.01f )
                {
                    new_move.x = new_move.x - temp_move.x;
                }
            }
        }
        return new_move;
    }
    return move;
}

} // namespace omi
